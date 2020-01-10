namespace Sledge.BspEditor.Environment.ShadowEngine
{
    partial class ShadowEngineEnviromentEditor
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.grpDirectories = new System.Windows.Forms.GroupBox();
            this.lblGameDir = new System.Windows.Forms.Label();
            this.btnGameDirBrowse = new System.Windows.Forms.Button();
            this.txtGameDir = new System.Windows.Forms.TextBox();
            this.grpDirectories.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpDirectories
            // 
            this.grpDirectories.Controls.Add(this.lblGameDir);
            this.grpDirectories.Controls.Add(this.btnGameDirBrowse);
            this.grpDirectories.Controls.Add(this.txtGameDir);
            this.grpDirectories.Location = new System.Drawing.Point(3, 3);
            this.grpDirectories.Name = "grpDirectories";
            this.grpDirectories.Size = new System.Drawing.Size(466, 227);
            this.grpDirectories.TabIndex = 0;
            this.grpDirectories.TabStop = false;
            this.grpDirectories.Text = "groupBox1";
            // 
            // lblGameDir
            // 
            this.lblGameDir.Location = new System.Drawing.Point(1, 19);
            this.lblGameDir.Name = "lblGameDir";
            this.lblGameDir.Size = new System.Drawing.Size(95, 20);
            this.lblGameDir.TabIndex = 17;
            this.lblGameDir.Text = "Game Dir";
            this.lblGameDir.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // btnGameDirBrowse
            // 
            this.btnGameDirBrowse.Location = new System.Drawing.Point(364, 19);
            this.btnGameDirBrowse.Name = "btnGameDirBrowse";
            this.btnGameDirBrowse.Size = new System.Drawing.Size(74, 20);
            this.btnGameDirBrowse.TabIndex = 18;
            this.btnGameDirBrowse.Text = "Browse...";
            this.btnGameDirBrowse.UseVisualStyleBackColor = true;
            // 
            // txtGameDir
            // 
            this.txtGameDir.Location = new System.Drawing.Point(102, 19);
            this.txtGameDir.Name = "txtGameDir";
            this.txtGameDir.Size = new System.Drawing.Size(256, 20);
            this.txtGameDir.TabIndex = 16;
            this.txtGameDir.Text = "example: C:\\Sierra\\Half-Life";
            // 
            // ShadowEngineEnviromentEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.grpDirectories);
            this.Name = "ShadowEngineEnviromentEditor";
            this.Size = new System.Drawing.Size(472, 233);
            this.grpDirectories.ResumeLayout(false);
            this.grpDirectories.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpDirectories;
        private System.Windows.Forms.Label lblGameDir;
        private System.Windows.Forms.Button btnGameDirBrowse;
        private System.Windows.Forms.TextBox txtGameDir;
    }
}
