using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;


namespace Arcasa
{
    class Program
    {
        public static string GetUsersAtFinal(string subString, string number)
        {
            string toReturn = null;
            int indexOfNumber = subString.IndexOf(number) + number.Length + 7;
            //bool ok = true;
            //bool start = true;
            //while (ok)
            //{
            //    if (subString[indexOfNumber].Equals(" ")  && start==false)
            //    {
            //        indexOfNumber++;
            //    }
            //    else if (subString[indexOfNumber].Equals(' ') == false)
            //    {

            //    }
            //}
            int indexOfSpace = subString.IndexOf(' ', indexOfNumber);
            if (indexOfSpace != -1)
                toReturn = subString.Substring(indexOfNumber, indexOfSpace - indexOfNumber);
            return toReturn;
        }

        public static List<string> getAllNumbers(string subString, string equipmentName)
        {
            List<string> toReturn = new List<string>();
            int i = -1;
            int indexOfName = subString.IndexOf(equipmentName);
            int indexOfSpace = subString.IndexOf(' ', indexOfName);
            int indexOfAnotherSpace = subString.IndexOf(' ', indexOfSpace + 1);
            string result = subString.Substring(indexOfSpace + 1, indexOfAnotherSpace - indexOfSpace - 1);
            //while result egal cu numar
            int n;
            bool isNumeric = int.TryParse(result, out n);
            while (isNumeric)
            {
                toReturn.Add(result);
                indexOfSpace = indexOfAnotherSpace;
                indexOfAnotherSpace = subString.IndexOf(' ', indexOfAnotherSpace + 1);
                result = subString.Substring(indexOfSpace + 1, indexOfAnotherSpace - indexOfSpace - 1);
                isNumeric = int.TryParse(result, out n);
            }

            return toReturn;


        }
        public static string GetTotalUsers(string subString, int index)
        {
            string toReturn = "";
            int indexOfInclude = subString.IndexOf("include", index + 1);
            int indexOfUserNumbers = subString.IndexOf("Total users", index + 1);
            int indexOfPuncte = subString.IndexOf(":", indexOfUserNumbers) + 2;
            int indexOfSpace = subString.IndexOf(" ", indexOfPuncte);
            if (indexOfUserNumbers != -1 && indexOfPuncte != -1 && indexOfSpace != -1)
            {
                toReturn = subString.Substring(indexOfPuncte, indexOfSpace - indexOfPuncte);
            }
            if (indexOfInclude > indexOfSpace || indexOfInclude == -1)
            {
                return toReturn;
            }
            return null;





        }
        public static string replaceCaracters(string subString)
        {

            subString = subString.Replace("\r", " ");
            subString = subString.Replace('\n', ' ');

            return subString;
        }

        public static Dictionary<int, string> GetName(string subString, int index)
        {
            int indexOfInclude = subString.IndexOf("include", index);
            if (indexOfInclude == -1) return null;
            int indexOfStartName = indexOfInclude + 8;
            int indexOfEndName = subString.IndexOf(' ', indexOfStartName);
            if (indexOfEndName != -1 && indexOfStartName != -1)
            {
                string name = subString.Substring(indexOfStartName, indexOfEndName - indexOfStartName);

                Dictionary<int, string> toReturn = new Dictionary<int, string>();
                toReturn.Add(indexOfEndName, name);
                return toReturn;
            }
            return null;
        }
        static void Main(string[] args)
        {
            string outputName = "C:\\Telefonica\\script\\output_" + DateTime.Now.ToString("yyyy-dd-M--HH-mm-ss") + ".txt";
            System.IO.StreamWriter file = new System.IO.StreamWriter(outputName);
            string equipmentName;
            string totalUsers = null;
            string firstFile = File.ReadAllText("C:\\Telefonica\\script\\1.txt");
            string secondFile = File.ReadAllText("C:\\Telefonica\\script\\2.txt");
            string thirdFile = File.ReadAllText("C:\\Telefonica\\script\\3.txt");


            firstFile = replaceCaracters(firstFile);
            secondFile = replaceCaracters(secondFile);
            thirdFile = replaceCaracters(thirdFile);

            for (int i = 0; i < firstFile.Length; i++)
            {
                Dictionary<int, string> names = GetName(firstFile, i);

                if (names != null)
                {
                    foreach (var name in names)
                    {
                        if (i > name.Key)
                        { goto Exit; }
                        i = name.Key;
                        equipmentName = name.Value;
                        totalUsers = GetTotalUsers(firstFile, i);
                        List<string> numbers = getAllNumbers(secondFile, equipmentName);
                        // verificam suma din fisierul 3 , return string
                        int totalUsersFinal = 0;
                        int totalUsersStart = 0;
                        int n = 0;

                        foreach (var number in numbers)
                        {

                            string resultThird = GetUsersAtFinal(thirdFile, number);
                            bool isNumeric = int.TryParse(resultThird, out n);
                            totalUsersFinal = totalUsersFinal + n;

                        }
                        bool result=false;
                        if (totalUsers != null)
                        result=int.TryParse(totalUsers, out totalUsersStart);
                        else totalUsersStart = 9999999;
                        if (result)
                        { 
                        Console.WriteLine("La echipamentul: " + equipmentName + " initial: " + totalUsersFinal.ToString().PadLeft(4, ' ') + " la final: " + totalUsersStart.ToString().PadLeft(4, ' ') + "  Diferenta: " + Math.Abs(totalUsersStart - totalUsersFinal));
                        string toPrint = "La echipamentul: " + equipmentName + " initial: " +
                                         totalUsersFinal.ToString().PadLeft(4, ' ') + " la final: " +
                                         totalUsersStart.ToString().PadLeft(4, ' ') + "  Diferenta: " +
                                         Math.Abs(totalUsersStart - totalUsersFinal) + '\n';
                        
                        file.WriteLine(toPrint);
}

                    }

                }
            }
            Exit:
            file.Close();
            Console.ReadLine();
        }
    }
}
