#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    FormAntivir::MyForm form; //WinFormsTest - имя вашего проекта
    Application::Run(% form);
}
