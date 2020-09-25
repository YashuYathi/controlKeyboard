#include <controlKeyboard.h>

void controlKeyboard::OnKeyDown(uint8_t _mod, uint8_t _oemKey) {
	modifiers = _mod;
	oemkey = _oemKey;
	keys_array[oemkey]=0;
	keydown = OemToAscii(_mod, _oemKey);
}

void controlKeyboard::OnKeyUp(uint8_t _mod, uint8_t _oemKey) {
	modifiers = _mod;
	oemkey = _oemKey;
	keys_array[oemkey]=1;
	keyup = OemToAscii(_mod, _oemKey);
}

bool controlKeyboard::onKeyPress(int k){
	if(keys_array[k] == 0)	
		return true;
	else
		return false;
}

bool controlKeyboard::onKeyRelease(int k){
	if(keys_array[k] == 1)	
		return true;
	else
		return false;
}

void controlKeyboard::setDefault(int k){
	keys_array[k] = 2;
}
