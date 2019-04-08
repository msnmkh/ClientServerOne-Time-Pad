using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace Server
{
    class OTP
    {
        // Encrypt with xor plain text and key
        public static string encrypt(string plainText)
        {
            string id, cipherText, key, MAC, result;
            // Split key and id 
            key = nextKey();
            id = key.Substring(1, 1);

            // Find Encrypt key in keys.txt
            key = key.Substring(3, key.Length - 3);

            // Decrypt key 
            //     byte[] k = Encoding.ASCII.GetBytes(key);
            //      key = AES.Decrypt(k);

            // Create cipher Text
            cipherText = xorString(plainText, key);

            // Create MAC
            MAC = createMac(cipherText);

            result = "ID:" + id + "enc:" + cipherText + "MAC:" + MAC;
            return result;
        }

        // Decrypt with xor cipher text and key
        public static string decrypt(string cipherText)
        {
            string key, decrypt, clientMAC, serverMAC, id="", cipher="";
            int i, j=0;

            // Separate MAC,CipherText,ID of key
            for (i = 0; i < cipherText.Length; i++)
            {
                if (cipherText[i] == 'e' && cipherText[i + 1] == 'n')
                {
                    id = cipherText.Substring(3, i - 3);
                    j = i + 4;
                }
                if (cipherText[i] == 'M' && cipherText[i + 1] == 'A')
                {
                    cipher = cipherText.Substring(j, i - j);
                    j = i + 4;
                }
            }
            clientMAC = cipherText.Substring(j, i - j);

            // Find key in kyes.txt
            key = findKEY(id);

            // Decrypt key
         //   byte[] k = Encoding.ASCII.GetBytes(key);
         //   key = AES.Decrypt(k);

            // Decrypt cipher text
            decrypt = xorString(cipher, key);

            // Create MAC with cipher text
            serverMAC = createMac(cipher);

            // Check mac for integrity
            if (serverMAC == clientMAC)
                Console.WriteLine("\nserver mac and client mac match :)) \t");
            else
                Console.WriteLine("\nserver mac and client mac does not match :)) \t");

            return decrypt;
        }

        // XOR two String
        private static string xorString(string str1, string str2)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < str1.Length; i++)
                sb.Append((char)(str1[i] ^ str2[(i % str2.Length)]));
            String result = sb.ToString();

            return result;
        }

        // Get next key odd key number that until not use from keys.txt file and write to serverSelectedKeys.txt
        public static string nextKey()
        {
            bool flag = false;
            Random rnd = new Random();
            string line = "";
            while (!flag)
            {
                int r = 1+(2*rnd.Next(0, 5));
                r = 3;
                List<string> found = new List<string>();
                using (StreamReader file = new StreamReader($"C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\keys.txt"))
                {
                    while ((line = file.ReadLine()) != null)
                    {
                    //    foreach (string lne in File.ReadLines($"C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\serverSelectedKeys.txt"))
                      //      if (lne == line) continue;

                        if (line.Contains("#3#"))
                        {
                            flag = true;
                            using (StreamWriter writer = new StreamWriter($"C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\serverSelectedKeys.txt"))
                            {
                                writer.WriteLine(line);
                            }
                            break;
                        }
                    }
                }
            }

          //  line = line.Substring(2,line.Length-3);

            return line;
        }

        // Create MAC for integrity
        public static string createMac(string cipherText)
        {
            SHA256 sha256 = SHA256.Create();
            byte[] bytes = Encoding.ASCII.GetBytes(cipherText);
            byte[] MAC = new byte[bytes.Length];
            MAC = sha256.ComputeHash(bytes);

            string mac = Encoding.ASCII.GetString(MAC);

            return mac;
        }

        // Find key that client used with id of keys
        public static string findKEY(string id)
        {
            string line = "";
            id = id + "#";
            List<string> found = new List<string>();
            using (StreamReader file = new StreamReader($"C:\\Users\\mohsen\\Documents\\Visual Studio 2017\\Projects\\ServerClient\\OneTimePad\\Server\\key\\keys.txt"))
            {
                while ((line = file.ReadLine()) != null)
                    if (line.Contains(id)) break;
             }
            line = line.Substring(id.Length+1,line.Length-id.Length-1);
            return line;
        }
    }
}

