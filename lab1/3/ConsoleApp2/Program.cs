namespace AverageCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            string input = "";
            if (args.Length > 0 && args[0] == "-f")
            {
                if (args.Length < 2)
                {
                    Console.WriteLine("Please provide the path to the file as a command line argument.");
                    return;
                }
                try
                {
                    input = File.ReadAllText(args[1]);
                }
                catch (FileNotFoundException)
                {
                    Console.WriteLine("File not found.");
                    return;
                }
            }
            else if(args.Length > 0 && args[0] == "-c")
            {
                Console.WriteLine("Enter a sequence of characters separated by spaces:");
                input = Console.ReadLine();
            }
            else if(args.Length == 0)
            {
                Console.WriteLine("Enter a sequence of characters separated by spaces (when writing real numbers, a comma is used):");
                input = Console.ReadLine();
            }
            else
            {
                Console.WriteLine("You entered the wrong flag");
                return;
            }

            string[] inputArray = input.Split(' ');

            int sum = 0;
            int count = 0;
            foreach (string item in inputArray)
            {
                foreach (char c in item)
                {
                    sum += (int)c;
                    count++;
                }
            }

            if (count > 0)
            {
                double average = (double)sum / count;
                Console.WriteLine("Average: " + average);
            }
            else
            {
                Console.WriteLine("No valid input provided.");
            }
        }
    }
}
