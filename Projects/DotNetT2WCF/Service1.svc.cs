using DotNetTema;

namespace DotNetT2WCF
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        

        public string SayHello(string name)
        {
            return string.Format("Bine ati venit, {0}", name);
        }

        string IService1.DisplayAllCars()
        {
            using (var context = new Model1Container())
            {
                string toReturn = "";
                int i = 0;
                toReturn += "Acestea sunt toate masinile: \n";
                var items = context.Cars;
                foreach (var x in items)                
                {
                    toReturn +=++i+" "+ x.BrandName + " " + x.ModelName + '\n';
                }
                return toReturn;
            }
        }

        public string PrintMenu()
        {
           return  "Alegeti una dintre optiunile urmatoare: \n 1. Afisati toate masinile \n 2. Afisati toate Companiile \n 3.Afisare informatii despre compania \n 4. Afisare toate masinile ale companiei \n 5. exit";

        }

        public string GetCompanyContacts(string name)
        {
            
            using (var context = new Model1Container())
            {
                var companies = context.Companies;
                foreach (var company in companies)
                {
                    if (company.CompanyName.Equals(name))
                    {
                        
                        return company.CompanyContact.Adress + " " + company.CompanyContact.Phone;
                    }
                }               
                    return "Nu sunt informatii despre compania" + name;               
            }
            


        }


        public string DisplayAllCompanyCarsByName(string name)
        {
            string toReturn="";
            int i = 0;
            using (var context = new Model1Container())
            {
                var companies = context.Companies;
                foreach (var company in companies)
                {
                    if (company.CompanyName.Equals(name))
                    {
                        foreach (var car in company.Cars)
                        {
                            toReturn += ++i + " " + car.BrandName + " " + car.ModelName + '\n';
                        }
                        return toReturn;
                    }
                }
                return "Nu sunt informatii despre compania" + name;
            }
        }


        public string DisplayAllCarsCompany()
        {
            using (var context = new Model1Container())
            {
                string toReturn = "";
                toReturn += "Acestea sunt toate Companiile care detin masini: \n";
                var items = context.Companies;
                foreach (var x in items)
                {
                    toReturn += x.CompanyName + '\n';
                }
                return toReturn;
            }
        }

       
    }
}
