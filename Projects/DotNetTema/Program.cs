using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DotNetTema
{
    class Program
    {
        static int newID=100;
        static void Main(string[] args)
        {
            Console.WriteLine("Model Designer First");
            DisplayAllCars();
            DisplayContactFromCompany("AutoRent");
            
            Console.ReadKey();
        }
        static void DisplayAllCars()
        {
            using (Model1Container context = new Model1Container())
            {
                Console.WriteLine("Acestea sunt toate masinile: ");
 
                 var items = context.Cars;
                foreach (var x in items)
                    Console.WriteLine("{0} {1}", x.BrandName, x.ModelName);
            }
        }

        static void DisplayContactFromCompany(string companyName)
        {
            using (Model1Container context = new Model1Container())
            {
              
                var items = context.Companies;
                foreach (var x in items)
                {
                    if (x.CompanyName.Equals(companyName))
                    {
                        
                        var items2 = context.CompanyContacts;
                        foreach (var y in items2)
                        {
                            if (y.ContactId == x.CompanyContact.ContactId)
                            {
                                Console.WriteLine("Contact details for " + companyName);
                                Console.WriteLine("Adress: {0} , PhoneNumber: {1}", y.Adress, y.Phone);
                            }
                        }

                    }
                }
                    
            }
        }


        //static void AddCarsToCompany(string companyName, string NewBrand, string NewModel)
        //{
        //    using (Model1Container context = new Model1Container())
        //    {

        //        Console.WriteLine("Adaugam masina {0} {1} la compania {2}: ", NewBrand, NewModel, companyName);
        //        int idComany ;
        //        var items = context.Companies;
        //        foreach (var x in items)
        //        {
        //            if (x.CompanyName.Equals(companyName))
        //            {
        //                idComany = x.CompanyId;

        //                newID++;
        //        Car car = new Car
        //        {

        //            BrandName = NewBrand,
        //            ModelName = NewModel,
        //            CompanyCompanyId = idComany

        //        };
        //        context.Cars.Add(car);
        //        context.SaveChanges();

        //    }
        //        }
        //    }
        //}

    }
}
