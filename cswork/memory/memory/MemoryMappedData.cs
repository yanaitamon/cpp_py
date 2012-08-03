using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;

namespace memory
{
  /// <summary>
  /// �������}�b�v�h�t�@�C���ő��v���Z�X�ƒʐM����N���X
  /// </summary>
  public class MemoryMappedData
  {
    //���L�������m�ۗp�̃n���h���ƃ|�C���^���`
    IntPtr m_memAreaHandle = IntPtr.Zero;
    IntPtr m_memAreaPointer = IntPtr.Zero;

    /// <summary>
    /// �������I�u�W�F�N�g�̊m��
    /// </summary>
    /// <param name="strObjectName">�}�b�v�I�u�W�F�N�g��</param>
    /// <param name="strlineNo">�������}�b�v�h�t�@�C���ɑ��镶����</param>
    /// <returns></returns>
    public unsafe bool CreateMemory(string strObjectName, string strline)
    {
      try
      {
        m_memAreaHandle = CreateFileMapping(//(UIntPtr)0xFFFFFFFF,	// �t�@�C���n���h��
                                            (UIntPtr)INVALID_HANDLE_VALUE,
                                            IntPtr.Zero,          // �Z�L�����e�B����
                                            0x04,                 // �ی쑮��(R/W)
                                            0,                    // �T�C�Y���
                                            1024,                 // �T�C�Y����
                                            strObjectName         // �I�u�W�F�N�g��
                                            );

        int retval = System.Runtime.InteropServices.Marshal.GetLastWin32Error();
        if (retval == ERROR_ALREADY_EXISTS)
        {
          // ���v���Z�X�Ŋ��ɍ쐬�ρ˃}�b�s���O�����Ȃ�
          m_memAreaPointer = MapViewOfFile(m_memAreaHandle, SECTION_ALL_ACCESS, 0, 0, 0);

          SharedData data;
          object obj = System.Runtime.InteropServices.Marshal.PtrToStructure(m_memAreaPointer, typeof(SharedData));

          data = (SharedData)obj;
          // �}�b�v�I�u�W�F�N�g�̏㏑��
          data.m_mylineNo = strline;
          System.Runtime.InteropServices.Marshal.StructureToPtr(data, m_memAreaPointer, false);
        }
        else
        {
          // ����Ȃ̂ŁA�f�[�^�}�b�s���O���s��
          // �G���A������������
          m_memAreaPointer = MapViewOfFile(m_memAreaHandle, SECTION_ALL_ACCESS, 0, 0, 0);

          SharedData data = new SharedData();
          data.m_url = "test������";
          data.m_mylineNo = strline;
          data.m_Value = 123;
          System.Runtime.InteropServices.Marshal.StructureToPtr(data, m_memAreaPointer, false);
        }
      }
      catch (Exception ex)
      {
        System.Diagnostics.Debug.WriteLine(ex.Message);
      }
      return false;
    }

    /// <summary>
    /// �������}�b�v�̉��
    /// </summary>
    /// <returns></returns>
    public unsafe bool UnmapViewOfFile()
    {
      try
      {
        UnmapViewOfFile(m_memAreaHandle);
      }
      catch (Exception ex)
      {
        System.Diagnostics.Debug.WriteLine(ex.Message);
      }
      return true;
    }

    // ���łɋ��L�������쐬�ς̏ꍇ�̃G���[�l
    const int ERROR_ALREADY_EXISTS = 183;

    // ���L�ɃA�N�Z�X�����ݒ�Ȃǂ��`����
    const UInt32 STANDARD_RIGHTS_REQUIRED = 0x000F0000;
    const UInt32 SECTION_QUERY = 0x0001;
    const UInt32 SECTION_MAP_WRITE = 0x0002;
    const UInt32 SECTION_MAP_READ = 0x0004;
    const UInt32 SECTION_MAP_EXECUTE = 0x0008;
    const UInt32 SECTION_EXTEND_SIZE = 0x0010;
    const UInt32 SECTION_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED
                                      | SECTION_QUERY
                                      | SECTION_MAP_WRITE
                                      | SECTION_MAP_READ
                                      | SECTION_MAP_EXECUTE
                                      | SECTION_EXTEND_SIZE);
    const UInt32 FILE_MAP_ALL_ACCESS = SECTION_ALL_ACCESS;

#if _X64
    const UInt64 INVALID_HANDLE_VALUE = 0xFFFFFFFFFFFFFFFF;  //((HANDLE)(LONG_PTR) - 1);
#else
    const UInt64 INVALID_HANDLE_VALUE = 0xFFFFFFFF;
#endif

    // ���L����������p��API��.NET�iC#�j�p�Ƀ}�[�V�������O���čĒ�`����
    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr CreateFileMapping(UIntPtr hFile, IntPtr lpFileMappingAttributes,
      uint flProtect, uint dwMaximumSizeHigh, uint dwMaximumSizeLow, string lpName);

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr MapViewOfFile(IntPtr hFileMappingObject, uint dwDesiredAccess,
      uint dwFileOffsetHigh, uint dwFileOffsetLow, uint dwNumberOfBytesToMap);

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr UnmapViewOfFile(IntPtr hFileMappingObject);
  }

  /// <summary>
  /// �e�X�g�p�̋��L�f�[�^�^
  /// </summary>
  struct SharedData
  {
    // ������̃}�[�V�������O
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
    public String m_mylineNo;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
    public String m_url;
    public int m_Value;
  }
}
