using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Server
{
    class Program
    {
        const int numberOfKyes = 10;

        static void Main(string[] args)
        {
         //    RandomKeyGenerator rnd = new RandomKeyGenerator();
          //         if (!rnd.CreateRandom(numberOfKyes))
            //          Console.WriteLine("Press any key to exit.");
           //      else {
             // New Object Server 
           Server server = new Server();
                
                // Listetn to client
                server.StartListening();
              //   }


         

            Console.ReadLine();
            Console.ReadLine();
        }
    }
}
