using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace memory
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      try
      {
        MemoryMappedData data = new MemoryMappedData();
        // "memory"�Ƃ�����ԂɃe�L�X�g�{�b�N�X�œ��͂��ꂽ�l���i�[����ꍇ
        data.CreateMemory("memory", textBox1.Text);
      }
      catch (Exception ex)
      {
        System.Diagnostics.Trace.WriteLine(ex.Message);
      }
    }
  }
}