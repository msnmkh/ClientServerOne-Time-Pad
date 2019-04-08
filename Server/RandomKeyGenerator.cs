using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Server
{
    class RandomKeyGenerator
    {
       // public List<int> CreateRandom(int numRows=2)
        public bool CreateRandom(int numRows=2)
        {
            Random rnd = new Random();
            List<int> result = new List<int>();
            string rd = "",s="";

            try
            {
                using (StreamWriter sw = new StreamWriter($"C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\keys.txt", false, Encoding.Default))
                {
                    for (int i = 0; i < numRows; i++)
                    {
                        rd = rnd.Next(0, 99999).ToString("D5");
                       // s = AES.Encrypt(rd);
                        sw.WriteLine("#" + i + "#" + rd);
                        //sw.WriteLine();
                    }
                }
                return true;
            }catch
            {
                return false;
            }
        }
    }
}
