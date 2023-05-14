#pragma once

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <filesystem>
#include <msclr\marshal_cppstd.h>


namespace FormAntivir {

	using namespace System;




	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;

	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::GroupBox^ groupBox1;



	protected:

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->panel2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 223);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(338, 30);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Выбрать директорию для сканирования";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(357, 223);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(553, 30);
			this->progressBar1->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 34);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 16);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Folders - ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 18);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Objects - ";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->richTextBox1);
			this->panel2->Location = System::Drawing::Point(357, 12);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(553, 199);
			this->panel2->TabIndex = 3;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(3, 3);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(547, 193);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(12, 15);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(338, 193);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Info";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(941, 264);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->panel2->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

#pragma region CustomFunc
		void getPathAndGo(std::filesystem::path folder, std::vector<std::filesystem::path> pathes, std::vector<int> base)
		{
			richTextBox1->Text += "-----------NewScan-----------\n";
			int tmpCountFiles = 0;
			int tmpCountFolders = 0;
			for (const auto& entry : std::filesystem::directory_iterator(folder)) {
				tmpCountFiles++;
				pathes.push_back(entry.path());
				if (std::filesystem::is_directory(entry.path())) {
					tmpCountFolders++;
					richTextBox1->Text += "path is folder - ";
					richTextBox1->Text += msclr::interop::marshal_as<System::String ^>(entry.path().string());
					richTextBox1->Text += "\n";
				}
			}
			this->Text = msclr::interop::marshal_as<System::String^>("Scanning derictory - " + folder.string());
			label2->Text = msclr::interop::marshal_as<System::String^>("Objects - " + std::to_string(tmpCountFiles));
			label3->Text = msclr::interop::marshal_as<System::String^>("Folders - " + std::to_string(tmpCountFolders));
			int d = tmpCountFiles - tmpCountFolders;
			go(pathes, base, d);
		}

		void go(std::vector<std::filesystem::path> pathes, std::vector<int> base, int d) {
			int processBarCount = 100 / d;
			for (std::filesystem::path p : pathes) {
				std::ifstream input(p, std::ios::binary);
				std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
				input.close();
				for (std::vector<char>::iterator it = buffer.begin(); it != buffer.end();) {
					bool exists = find(begin(base), end(base), *it) != end(base);
					if (exists) {
						richTextBox1->Text += "VIRUS!!! - ";
						richTextBox1->Text += msclr::interop::marshal_as<System::String^>(p.string());
						richTextBox1->Text += "\n";
						this->progressBar1->Increment(processBarCount + (100 % d));
						break;
					} 
					else {
						richTextBox1->Text += "CLEAR - ";
						richTextBox1->Text += msclr::interop::marshal_as<System::String^>(p.string());
						richTextBox1->Text += "\n";
						this->progressBar1->Increment(processBarCount + (100 % d));
						break;
					}
				}
				buffer.clear();
			}
		}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ folderScan = folderBrowserDialog1->SelectedPath;
			std::vector<std::filesystem::path> pathes;
			std::vector<int> base = { 5, 8, 2 };
			if (progressBar1->Value >= 100) progressBar1->Value = 0;
			getPathAndGo(msclr::interop::marshal_as<std::string>(folderScan), pathes, base);
		}
	}
#pragma endregion
};
}
