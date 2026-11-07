#pragma once

namespace Futkeeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;	// For working with files

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: add constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fILEToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ createUserToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openUserToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ controlsUsersToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ settingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;


	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col2;









	protected:








	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fILEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createUserToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openUserToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->controlsUsersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->col1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->col2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->Location = System::Drawing::Point(6, 19);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(116, 21);
			this->comboBox1->TabIndex = 0;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fILEToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(988, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fILEToolStripMenuItem
			// 
			this->fILEToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->createUserToolStripMenuItem,
					this->openUserToolStripMenuItem, this->controlsUsersToolStripMenuItem
			});
			this->fILEToolStripMenuItem->Name = L"fILEToolStripMenuItem";
			this->fILEToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fILEToolStripMenuItem->Text = L"File";
			this->fILEToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fILEToolStripMenuItem_Click);
			// 
			// createUserToolStripMenuItem
			// 
			this->createUserToolStripMenuItem->Name = L"createUserToolStripMenuItem";
			this->createUserToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->createUserToolStripMenuItem->Text = L"Create User";
			// 
			// openUserToolStripMenuItem
			// 
			this->openUserToolStripMenuItem->Name = L"openUserToolStripMenuItem";
			this->openUserToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->openUserToolStripMenuItem->Text = L"Open User";
			// 
			// controlsUsersToolStripMenuItem
			// 
			this->controlsUsersToolStripMenuItem->Name = L"controlsUsersToolStripMenuItem";
			this->controlsUsersToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->controlsUsersToolStripMenuItem->Text = L"Controls Users";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->settingsToolStripMenuItem,
					this->helpToolStripMenuItem1, this->aboutToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// settingsToolStripMenuItem
			// 
			this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
			this->settingsToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->settingsToolStripMenuItem->Text = L"Settings";
			// 
			// helpToolStripMenuItem1
			// 
			this->helpToolStripMenuItem1->Name = L"helpToolStripMenuItem1";
			this->helpToolStripMenuItem1->Size = System::Drawing::Size(116, 22);
			this->helpToolStripMenuItem1->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Location = System::Drawing::Point(200, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(172, 58);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Account";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->splitContainer1, 0, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 27);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(375, 225);
			this->tableLayoutPanel1->TabIndex = 5;
			// 
			// panel1
			// 
			this->panel1->AutoSize = true;
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(32, 0);
			this->panel1->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Right;
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(32, 0);
			this->button1->TabIndex = 6;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(0, 0);
			this->textBox1->MinimumSize = System::Drawing::Size(100, 20);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 5;
			// 
			// splitContainer1
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->splitContainer1, 2);
			this->splitContainer1->Location = System::Drawing::Point(3, 67);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->listBox1);
			this->splitContainer1->Panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::splitContainer1_Panel1_Paint);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->dataGridView1);
			this->splitContainer1->Panel2->Controls->Add(this->label1);
			this->splitContainer1->Size = System::Drawing::Size(369, 155);
			this->splitContainer1->SplitterDistance = 119;
			this->splitContainer1->TabIndex = 7;
			// 
			// listBox1
			// 
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(0, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(119, 155);
			this->listBox1->TabIndex = 7;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToOrderColumns = true;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->col1, this->col2 });
			this->dataGridView1->Location = System::Drawing::Point(3, 16);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(245, 142);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellContentClick);
			// 
			// col1
			// 
			this->col1->HeaderText = L"Param";
			this->col1->Name = L"col1";
			// 
			// col2
			// 
			this->col2->HeaderText = L"Value";
			this->col2->Name = L"col2";
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(100, 0);
			this->label1->MaximumSize = System::Drawing::Size(100, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(988, 620);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L" u";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void openUserToolStripMenuItem(System::Object^ sender, System::EventArgs^ e) 
	{
		   String^ FileName = "";	// Variable that stores the path to the file

		   if (openUserToolStripMenuItem-> ShowDialog() == Windows::Forms::DialogResult::OK)	// Open the dialog; if the user pressed OK then...
		   {
			   FileName = openUserToolStripMenuItem -> FileName;	// Store the path of the selected file
		   }
		   // Guard against errors (it would work without it too)
		   try
		   {
			   StreamReader^ file = File::OpenText(FileName);	// Open the file
			   textBox1->Text = file->ReadToEnd();	// Write the content to Text

		   }catch(Exception^ e)
		   {
			   MessageBox::Show(this, "Файл не был открыт", "Ошибка", MessageBoxButtons::OK, MessageBoxButtons::Error);
		   }
			   
	}

	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

	private: System::Void fILEToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void splitContainer1_Panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
