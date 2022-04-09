
namespace wasilewskijWinForms
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.langBox = new System.Windows.Forms.GroupBox();
            this.ANGbutton = new System.Windows.Forms.Button();
            this.POLbutton = new System.Windows.Forms.Button();
            this.GetdataBox = new System.Windows.Forms.GroupBox();
            this.ReadButton = new System.Windows.Forms.Button();
            this.SaveButton = new System.Windows.Forms.Button();
            this.EditBox = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.CollorButton = new System.Windows.Forms.Button();
            this.showCollor = new System.Windows.Forms.Label();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.RemoveVertexButton = new System.Windows.Forms.Button();
            this.ClearGraphButton = new System.Windows.Forms.Button();
            this.Canvas = new System.Windows.Forms.PictureBox();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.langBox.SuspendLayout();
            this.GetdataBox.SuspendLayout();
            this.EditBox.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            resources.ApplyResources(this.tableLayoutPanel1, "tableLayoutPanel1");
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.Canvas, 0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            // 
            // tableLayoutPanel2
            // 
            resources.ApplyResources(this.tableLayoutPanel2, "tableLayoutPanel2");
            this.tableLayoutPanel2.Controls.Add(this.langBox, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.GetdataBox, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.EditBox, 0, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            // 
            // langBox
            // 
            resources.ApplyResources(this.langBox, "langBox");
            this.langBox.Controls.Add(this.ANGbutton);
            this.langBox.Controls.Add(this.POLbutton);
            this.langBox.Name = "langBox";
            this.langBox.TabStop = false;
            // 
            // ANGbutton
            // 
            resources.ApplyResources(this.ANGbutton, "ANGbutton");
            this.ANGbutton.Name = "ANGbutton";
            this.ANGbutton.UseVisualStyleBackColor = true;
            this.ANGbutton.Click += new System.EventHandler(this.ENGbutton_Click);
            // 
            // POLbutton
            // 
            resources.ApplyResources(this.POLbutton, "POLbutton");
            this.POLbutton.Name = "POLbutton";
            this.POLbutton.UseVisualStyleBackColor = true;
            this.POLbutton.Click += new System.EventHandler(this.POLbutton_Click);
            // 
            // GetdataBox
            // 
            this.GetdataBox.Controls.Add(this.ReadButton);
            this.GetdataBox.Controls.Add(this.SaveButton);
            resources.ApplyResources(this.GetdataBox, "GetdataBox");
            this.GetdataBox.Name = "GetdataBox";
            this.GetdataBox.TabStop = false;
            // 
            // ReadButton
            // 
            resources.ApplyResources(this.ReadButton, "ReadButton");
            this.ReadButton.Name = "ReadButton";
            this.ReadButton.UseVisualStyleBackColor = true;
            this.ReadButton.Click += new System.EventHandler(this.ReadButton_Click);
            // 
            // SaveButton
            // 
            resources.ApplyResources(this.SaveButton, "SaveButton");
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // EditBox
            // 
            resources.ApplyResources(this.EditBox, "EditBox");
            this.EditBox.Controls.Add(this.tableLayoutPanel5);
            this.EditBox.Name = "EditBox";
            this.EditBox.TabStop = false;
            // 
            // tableLayoutPanel5
            // 
            resources.ApplyResources(this.tableLayoutPanel5, "tableLayoutPanel5");
            this.tableLayoutPanel5.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.tableLayoutPanel4, 0, 1);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            // 
            // tableLayoutPanel3
            // 
            resources.ApplyResources(this.tableLayoutPanel3, "tableLayoutPanel3");
            this.tableLayoutPanel3.Controls.Add(this.CollorButton, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.showCollor, 1, 0);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            // 
            // CollorButton
            // 
            resources.ApplyResources(this.CollorButton, "CollorButton");
            this.CollorButton.Name = "CollorButton";
            this.CollorButton.UseVisualStyleBackColor = true;
            this.CollorButton.Click += new System.EventHandler(this.colorDialog_click);
            // 
            // showCollor
            // 
            this.showCollor.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            resources.ApplyResources(this.showCollor, "showCollor");
            this.showCollor.Name = "showCollor";
            // 
            // tableLayoutPanel4
            // 
            resources.ApplyResources(this.tableLayoutPanel4, "tableLayoutPanel4");
            this.tableLayoutPanel4.Controls.Add(this.RemoveVertexButton, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.ClearGraphButton, 0, 1);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            // 
            // RemoveVertexButton
            // 
            resources.ApplyResources(this.RemoveVertexButton, "RemoveVertexButton");
            this.RemoveVertexButton.Name = "RemoveVertexButton";
            this.RemoveVertexButton.UseVisualStyleBackColor = true;
            this.RemoveVertexButton.Click += new System.EventHandler(this.RemoveVertexButton_Click);
            // 
            // ClearGraphButton
            // 
            resources.ApplyResources(this.ClearGraphButton, "ClearGraphButton");
            this.ClearGraphButton.Name = "ClearGraphButton";
            this.ClearGraphButton.UseVisualStyleBackColor = true;
            this.ClearGraphButton.Click += new System.EventHandler(this.ClearGraphButton_Click);
            // 
            // Canvas
            // 
            resources.ApplyResources(this.Canvas, "Canvas");
            this.Canvas.Name = "Canvas";
            this.Canvas.TabStop = false;
            this.Canvas.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MoveVert);
            this.Canvas.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MoveVertex);
            this.Canvas.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Delmovevert);
            // 
            // Form1
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.SizeChanged += new System.EventHandler(this.resize);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.dellpress);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.langBox.ResumeLayout(false);
            this.GetdataBox.ResumeLayout(false);
            this.EditBox.ResumeLayout(false);
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.GroupBox EditBox;
        private System.Windows.Forms.GroupBox langBox;
        private System.Windows.Forms.GroupBox GetdataBox;
        private System.Windows.Forms.Button ANGbutton;
        private System.Windows.Forms.Button POLbutton;
        private System.Windows.Forms.Button ReadButton;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Button CollorButton;
        private System.Windows.Forms.Label showCollor;
        private System.Windows.Forms.PictureBox Canvas;
        private System.Windows.Forms.Button RemoveVertexButton;
        private System.Windows.Forms.Button ClearGraphButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
    }
}

