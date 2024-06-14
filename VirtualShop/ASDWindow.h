#pragma once
#include <conio.h>
#include "ASDString.h"
#include "ASDArray.h"
#include "fun_console.h"

namespace ASD {
	class Window
	{
	protected:
		int x, y, width, height;
		int color, bgColor, borderColor;
		char buf[6];
	public:
		Window();
		Window & Move(int _x, int _y);
		int GetColor() { return color; }
		int GetBgColor() { return bgColor; }
		int GetBorderColor() { return borderColor; }
		int GetX() { return x; }
		int GetY() { return y; }
		int GetWidth() { return width; }
		int GetClientWidth() { return width - 2; }
		int GetHeight() { return height; }
		int GetClientHeight() { return height - 2; }
		Window & HCenter();
		Window & VCenter();
		Window & SetColor(int c);
		Window & SetBorderColor(int c);
		Window & SetBgColor(int c);
		Window & SetWidth(int w);
		Window & SetHeight(int h);
		Window & Show();
		Window & Write(int, int, const char *);
		virtual void Draw() {}
	};

	
	class Message: public Window {
		protected:
			String text;
		public:
			Message(String t) :text(t) {}
			void Draw() { std::cout << text;}
			
			//Message & Show() {
			//	Window::Show();
			//	std::cout << text; _getch();
			//	return *this;
			//}
			
	};
	
	

	class Menu: public Window {
		protected:
			Array<String> items;
			int active;
			int selectColor, selectBgColor;
			int first;
		public:
			Menu(): Window() {
				active = -1;
				selectColor = LightGreen;
				selectBgColor = White;
			}
			Menu & Add(String m) { items.Add(m); return *this; }
			int GetSelect() { return active;  }
			int Select();
		
	};


}

