#include "guichannel.h"
#include "midi.h"
#include "font.h"
#include "palette.h"

GUIChannel::GUIChannel(Channel * c, int n, Copy * copy, Synth * synth)
	: GUIElement(48+n*(48+8), 48, 48, 408), channel(c), number(n), offset(0),
		selectBegin(-1), selectEnd(-1), mousedown(false), shift(false),
		copy(copy), synth(synth)
{
	if ( n == 0 ) {
		selectBegin = 0;
		selectEnd = 1;
	}
	update();
	lastNote.active = true;
	lastNote.note = 60;
	lastNote.volume = 10;
}

void GUIChannel::update()
{
	char str[7];

	clear();

	sprintf(str, "%2d", channel->duty);
	if ( number < 6 )
		fontPrint(surface, str, 29, 0, paletteColor(6));

	sprintf(str, "%2d", channel->dec);
	fontPrint(surface, str, 29, 8, paletteColor(6));

	if ( selectBegin >= 0 && selectBegin < offset+48 ) {
		int b = selectBegin - offset;
		int e = selectEnd - offset;
		if ( b < 0 )
			b = 0;
		else if ( b >= 47 )
			b = 47;
		if ( e < 0 )
			e = 0;
		else if ( e >= 48 )
			e = 48;
		unsigned int c = paletteColor(2);
		unsigned int * pix = (unsigned int *) surface->pixels
			+ b * 8*8*6 + 8*6*21;
		if ( e - b > 0 )
			for ( int i = (e-b)*8*8*6 ; i > 0 ; i-- )
				*pix++ = c;
	}

	for ( int i = 0 ; i < 48 ; i++ ) {
		if ( channel->notes[i+offset].active ) {
			sprintf(str, "%s %2d",
					midiNoteName(channel->notes[i+offset].note),
					channel->notes[i+offset].volume);
			fontPrint(surface, str, 0, 21+i*8, paletteColor(4));
		} else {
			fontPrint(surface, "___ __", 0, 21+i*8, paletteColor(1));
		}
	}
}

bool GUIChannel::process(SDL_Event * event)
{
	bool catched = false;

	if ( event->type == SDL_MOUSEBUTTONUP && event->button.button == 1 ) {
		mousedown = false;
		if ( selectBegin > -1 && test(event->button.x, event->button.y) ) {
			int tmp = event->button.y - 48;
			if ( tmp > y ) {
				selectEnd = (tmp-3)/8 - 2 + offset + 1;
			} else {
				selectEnd = selectBegin+1;
				selectBegin = (tmp-3)/8 - 2 + offset;
			}
			catched = true;
		}
	} else if ( event->type == SDL_MOUSEBUTTONDOWN ) {
		if ( event->button.button == 5 ) // wheel down : scroll down
			offset++;
		else if ( event->button.button == 4 ) // wheel up : scroll up
			offset--;
		else if ( event->button.button == 1 ) { // mouse click : select & edit
			if ( test(event->button.x, event->button.y) ) {
				y = event->button.y - 48;
				x = event->button.x - area.x;
				if ( y < 8 )
					selectBegin = EDITDUTY;
				else if ( y < 16 )
					selectBegin = EDITDEC;
				else if ( y > 21 )
					selectBegin = (y-3)/8 - 2 + offset;
				selectEnd = selectBegin + 1;
				mousedown = true;
			} else if ( selectBegin != -1 )
				selectBegin = -1;
		}
		catched = true;
	} else if ( event->type == SDL_MOUSEMOTION && mousedown
			&& selectBegin < -1 ) { // edit mode
		int dy = (event->motion.y-48) - y;
		if ( dy > DELTA || dy < -DELTA ) {
			if ( dy > DELTA )
				y += DELTA;
			else
				y -= DELTA;

			if ( selectBegin == EDITDUTY && number < 6 ) { // edit duty
				if ( dy > DELTA && channel->duty < 6 )
					channel->duty++;
				else if ( dy < -DELTA && channel->duty > 0 )
					channel->duty--;
				synth->setChannelDuty(number, channel->duty);
			} else if ( selectBegin == EDITDEC ) { // edit decrease rate
				if ( dy > DELTA && channel->dec < 99 )
					channel->dec++;
				else if ( dy < -DELTA && channel->dec > 0 )
					channel->dec--;
			}

			catched = true;
		}
	} else if ( event->type == SDL_KEYDOWN ) {
		if ( event->key.keysym.sym == SDLK_PAGEDOWN ) { // page down
			offset += 48;
			catched = true;
		} else if ( event->key.keysym.sym == SDLK_PAGEUP ) { // page up
			offset -= 48;
			catched = true;
		} else if ( selectBegin >= 0 ) {
			if ( event->key.keysym.sym == SDLK_DOWN ) { // move/select down
				if ( selectBegin < MAXROWS-1 && selectEnd < MAXROWS ) {
					if ( shift )
						selectEnd++;
					else {
						selectBegin++;
						selectEnd = selectBegin+1;
					}
					catched = true;
				}
				if ( selectEnd >= offset + 48 && selectEnd < MAXROWS )
					PushUserEvent(GUI_SETOFFSET, (void *)(offset+10));
			} else if ( event->key.keysym.sym == SDLK_UP ) { // move/select up
				if ( shift && selectBegin != selectEnd-1 ) {
					selectEnd--;
					catched = true;
				} else if ( selectBegin > 0 ) {
					selectBegin--;
					selectEnd = selectBegin+1;
					catched = true;
				}
				if ( selectEnd <= offset && selectBegin > 0 )
					PushUserEvent(GUI_SETOFFSET, (void *)(offset-10));
			} else if ( event->key.keysym.sym == SDLK_RETURN ) { // note on/off
				if ( selectBegin == selectEnd-1 ) {
					if ( channel->notes[selectBegin].active ) {
						lastNote = channel->notes[selectBegin];
						channel->deleteNote(selectBegin);
					} else {
						channel->setNote(selectBegin, lastNote);
					}
				} else {
					for ( int i = selectBegin ; i < selectEnd ; i++ )
						channel->deleteNote(i);
				}
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_LEFT ) { // move left
				if ( number > 0 ) {
					PushUserEvent(GUI_SETCHANNEL,
							(void *)(number-1), (void *)selectBegin);
					selectBegin = -1;
					catched = true;
				}
			} else if ( event->key.keysym.sym == SDLK_RIGHT ) { // move right
				if ( number < 7 ) {
					PushUserEvent(GUI_SETCHANNEL,
							(void *)(number+1), (void *)selectBegin);
					selectBegin = -1;
					catched = true;
				}
			} else if ( event->key.keysym.sym == SDLK_d ) { // note -
				if ( selectBegin == selectEnd-1
						&& ! channel->notes[selectBegin].active ) {
					channel->setNote(selectBegin, lastNote);
				} else {
					for ( int i = selectBegin ; i < selectEnd ; i++ ) {
						if ( channel->notes[i].active
								&& channel->notes[i].note > 0 ) {
							channel->notes[i].note--;
							if ( i == selectBegin )
								lastNote = channel->notes[i];
						}
					}
				}
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_g ) { // note +
				if ( selectBegin == selectEnd-1
						&& ! channel->notes[selectBegin].active ) {
					channel->setNote(selectBegin, lastNote);
				} else {
					for ( int i = selectBegin ; i < selectEnd ; i++ ) {
						if ( channel->notes[i].active
								&& channel->notes[i].note < 127 ) {
							channel->notes[i].note++;
							if ( i == selectBegin )
								lastNote = channel->notes[i];
						}
					}
				}
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_e ) { // volume -
				if ( selectBegin == selectEnd-1
						&& ! channel->notes[selectBegin].active ) {
					channel->notes[selectBegin] = lastNote;
				} else {
					for ( int i = selectBegin ; i < selectEnd ; i++ ) {
						if ( channel->notes[i].active
								&& channel->notes[i].volume > 0 ) {
							channel->notes[i].volume--;
							if ( i == selectBegin )
								lastNote = channel->notes[i];
						}
					}
				}
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_t ) { // volume +
				if ( selectBegin == selectEnd-1
						&& ! channel->notes[selectBegin].active ) {
					channel->notes[selectBegin] = lastNote;
				} else {
					for ( int i = selectBegin ; i < selectEnd ; i++ ) {
						if ( channel->notes[i].active
								&& channel->notes[i].volume < 31 ) {
							channel->notes[i].volume++;
							if ( i == selectBegin )
								lastNote = channel->notes[i];
						}
					}
				}
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_RCTRL 
					|| event->key.keysym.sym == SDLK_LCTRL ) { // set cursor
				synth->setRow(selectBegin);
			} else if ( event->key.keysym.sym == SDLK_x ) { // cut
				copy->size = selectEnd - selectBegin;
				memcpy(copy->notes, & channel->notes[selectBegin],
						copy->size * sizeof(Note));
				for ( int i = selectBegin ; i < selectEnd ; i++ )
					channel->deleteNote(i);
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_c ) { // copy
				copy->size = selectEnd - selectBegin;
				memcpy(copy->notes, & channel->notes[selectBegin],
						copy->size * sizeof(Note));
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_v ) { // paste
				memcpy(& channel->notes[selectBegin], copy->notes,
						copy->size * sizeof(Note));
				if ( channel->lastRow < selectBegin + copy->size )
					channel->lastRow = selectBegin + copy->size;
				catched = true;
			} else if ( event->key.keysym.sym == SDLK_LSHIFT
					|| event->key.keysym.sym == SDLK_RSHIFT )
				shift = true;
		}
	} else if ( event->type == SDL_KEYUP ) {
		if ( event->key.keysym.sym == SDLK_LSHIFT
				|| event->key.keysym.sym == SDLK_RSHIFT )
			shift = false;
	} else if ( event->type == SDL_USEREVENT ) {
		if ( event->user.code == GUI_SETOFFSET ) {
			offset = *(int*)&event->user.data1;
			catched = true;
		} else if ( event->user.code == GUI_SETCHANNEL ) {
			int n = *(int*)&event->user.data1;
			int s = *(int*)&event->user.data2;
			if ( selectBegin >= 0 && selectEnd == selectBegin+1 ) {
				if ( n != number ) {
					selectBegin = -1;
					catched = true;
				}
			} else if ( n == number ) {
				selectBegin = s;
				selectEnd = s+1;
				catched = true;
			}
		}
	}

	if ( catched ) {
		if ( offset < 0 )
			offset = 0;
		if ( offset >= MAXROWS - 48 )
			offset = MAXROWS - 48;
		update();
	}

	return catched;
}
