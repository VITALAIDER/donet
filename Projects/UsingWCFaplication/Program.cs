using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UsingWCFaplication.ServiceReference1;

namespace UsingWCFaplication
{
    class Program
    {
        static void Main(string[] args)
        {
            string userName;
            string choose ="6";
            Service1Client newClient = new Service1Client();
            Console.WriteLine("Va rugam introduceti numele dvs:");
            userName = Console.ReadLine();
            Console.WriteLine(newClient.SayHello(userName));
            while (choose.Equals("5") == false)
            {
                Console.WriteLine(newClient.PrintMenu());
                choose = Console.ReadLine();
                if(choose.Equals("1"))
                Console.WriteLine(newClient.DisplayAllCars());
                if (choose.Equals("2"))
                Console.WriteLine(newClient.DisplayAllCarsCompany());
                if (choose.Equals("3"))
                {
                    string name= Console.ReadLine();
                    Console.WriteLine(newClient.GetCompanyContacts(name));
                }
                if (choose.Equals("4"))
                {
                    string name = Console.ReadLine();
                    Console.WriteLine(newClient.DisplayAllCompanyCarsByName(name));
                }
                if (choose.Equals("5"))
                    break;
                
            }
            //newClient.SayHello()
            Console.ReadLine();
        }
    }
}
