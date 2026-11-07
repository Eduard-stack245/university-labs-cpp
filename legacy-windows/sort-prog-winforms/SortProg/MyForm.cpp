#include "MyForm.h"
#include <Windows.h>

using namespace SortProg; // Project name

[STAThread]	// Without this the file dialog cannot be opened

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm);
	return 0;
}