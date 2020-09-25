#ifndef CONTROL_KEYBOARD_H
#define CONTROL_KEYBOARD_H

#include <hidboot.h>
enum KeyboardModifiers {
	LeftCtrl = 1,
	LeftShift = 2,
	Alt = 4,
	LeftCmd = 8,
	RightCtrl = 16,
	RightShift = 32,
	AltGr = 64,
	RightCmd = 128
};

//key array contains state of keys 0 - Pressed, 1 - Released and 2 - Nothing

const int KEY_ARRAY_SIZE = 100;

class controlKeyboard : public KeyboardReportParser {
public:
  	controlKeyboard(USBHost &usb) : hostKeyboard(&usb), keyup(0),keydown(0), oemkey(0), modifiers(0) {
    	hostKeyboard.SetReportParser(0, this);
		for(int i=0;i<KEY_ARRAY_SIZE;i++){
			keys_array[i] = 2;
		}		
  	};

  	bool onKeyPress(int k);
  	bool onKeyRelease(int k);
	void setDefault(int k);
  	uint8_t getKeyup(){ return keyup; };
  	uint8_t getKeydown(){ return keydown; };
  	uint8_t getModifiers(){ return modifiers; };
  	uint8_t getOemKey(){ return oemkey; };

protected:
  	virtual void OnKeyDown(uint8_t mod, uint8_t key);
  	virtual void OnKeyUp(uint8_t mod, uint8_t key);
private:
  	uint8_t keyup, keydown, oemkey, modifiers;
  	HIDBoot<HID_PROTOCOL_KEYBOARD> hostKeyboard;
	int keys_array[KEY_ARRAY_SIZE];
};
#endif
