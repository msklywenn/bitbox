#ifndef _GUIEVENTS_H_
#define _GUIEVENTS_H_

#define GUI_SETOFFSET 0
#define GUI_SETCHANNEL 1
#define GUI_CURRENTROW 2
#define GUI_OSCILLOSCOPE 3
#define GUI_STATUS 4

void PushUserEvent(int code, void * data1 = 0, void * data2 = 0);

#endif // _GUIEVENTS_H_
