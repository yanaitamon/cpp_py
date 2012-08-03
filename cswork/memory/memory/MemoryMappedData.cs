using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;

namespace memory
{
  /// <summary>
  /// メモリマップドファイルで他プロセスと通信するクラス
  /// </summary>
  public class MemoryMappedData
  {
    //共有メモリ確保用のハンドルとポインタを定義
    IntPtr m_memAreaHandle = IntPtr.Zero;
    IntPtr m_memAreaPointer = IntPtr.Zero;

    /// <summary>
    /// メモリオブジェクトの確保
    /// </summary>
    /// <param name="strObjectName">マップオブジェクト名</param>
    /// <param name="strlineNo">メモリマップドファイルに送る文字列</param>
    /// <returns></returns>
    public unsafe bool CreateMemory(string strObjectName, string strline)
    {
      try
      {
        m_memAreaHandle = CreateFileMapping(//(UIntPtr)0xFFFFFFFF,	// ファイルハンドル
                                            (UIntPtr)INVALID_HANDLE_VALUE,
                                            IntPtr.Zero,          // セキュリティ属性
                                            0x04,                 // 保護属性(R/W)
                                            0,                    // サイズ上位
                                            1024,                 // サイズ下位
                                            strObjectName         // オブジェクト名
                                            );

        int retval = System.Runtime.InteropServices.Marshal.GetLastWin32Error();
        if (retval == ERROR_ALREADY_EXISTS)
        {
          // 他プロセスで既に作成済⇒マッピング処理なし
          m_memAreaPointer = MapViewOfFile(m_memAreaHandle, SECTION_ALL_ACCESS, 0, 0, 0);

          SharedData data;
          object obj = System.Runtime.InteropServices.Marshal.PtrToStructure(m_memAreaPointer, typeof(SharedData));

          data = (SharedData)obj;
          // マップオブジェクトの上書き
          data.m_mylineNo = strline;
          System.Runtime.InteropServices.Marshal.StructureToPtr(data, m_memAreaPointer, false);
        }
        else
        {
          // 初回なので、データマッピングを行う
          // エリアを初期化する
          m_memAreaPointer = MapViewOfFile(m_memAreaHandle, SECTION_ALL_ACCESS, 0, 0, 0);

          SharedData data = new SharedData();
          data.m_url = "test文字列";
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
    /// メモリマップの解放
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

    // すでに共有メモリ作成済の場合のエラー値
    const int ERROR_ALREADY_EXISTS = 183;

    // 下記にアクセス制限設定などを定義する
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

    // 共有メモリ制御用のAPIを.NET（C#）用にマーシャリングして再定義する
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
  /// テスト用の共有データ型
  /// </summary>
  struct SharedData
  {
    // 文字列のマーシャリング
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
    public String m_mylineNo;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
    public String m_url;
    public int m_Value;
  }
}
