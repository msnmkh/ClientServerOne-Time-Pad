using System;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace Server
{
    class AES
    {
        private static byte[] Key = { 182, 131, 35, 156, 149, 66, 53, 237, 238, 163, 214, 71, 31, 10, 30, 124, 156, 226, 105, 111, 253, 124, 38, 72, 234, 126, 230, 5, 39, 37, 121, 230 };
        private static byte[] IV = { 1, 64, 119, 95, 10, 132, 5, 137, 103, 8, 100, 14, 91, 34, 81, 197 };
        //  Encryption message
        public static string Encrypt(string plainText)
        {
            byte[] encrypted;
            // Create a new AesManaged.    
            using (AesManaged aes = new AesManaged())
            {
                aes.Mode = CipherMode.CBC;
                aes.Padding = PaddingMode.Zeros;
                // Create encryptor    
                ICryptoTransform encryptor = aes.CreateEncryptor(Key, IV);
                // Create MemoryStream    
                using (MemoryStream ms = new MemoryStream())
                {
                    // Create crypto stream using the CryptoStream class. This class is the key to encryption    
                    // and encrypts and decrypts data from any given stream. In this case, we will pass a memory stream    
                    // to encrypt    
                    using (CryptoStream cs = new CryptoStream(ms, encryptor, CryptoStreamMode.Write))
                    {
                        // Create StreamWriter and write data to a stream    
                        using (StreamWriter sw = new StreamWriter(cs))
                            sw.Write(plainText);
                        encrypted = ms.ToArray();
                    }
                }
            }
            string enc = Encoding.ASCII.GetString(encrypted);
            // Return encrypted data    
            return enc;
        }

        //  Decryption encrypt message
        public static string Decrypt(byte[] cipherText)
        {
            string plaintext = null;
            // Create AesManaged    
            using (AesManaged aes = new AesManaged())
            {
                aes.Mode = CipherMode.CBC;
                aes.Padding = PaddingMode.Zeros;
                // Create a decryptor    
                ICryptoTransform decryptor = aes.CreateDecryptor(Key, IV);
                // Create the streams used for decryption.    
                using (MemoryStream ms = new MemoryStream(cipherText))
                {
                    // Create crypto stream    
                    using (CryptoStream cs = new CryptoStream(ms, decryptor, CryptoStreamMode.Read))
                    {
                        // Read crypto stream    
                        using (StreamReader reader = new StreamReader(cs))
                            plaintext = reader.ReadToEnd();
                    }
                }
            }
            return plaintext;
        }
    }
}
