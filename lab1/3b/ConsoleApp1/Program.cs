namespace NumberProcessingApp
{
    class Program
    {
        static void Main(string[] args)
        {
            string input;
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

            string[] numberStrings = input.Split(new char[] { ' ', '\t', '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);

            double[] numbers = new double[numberStrings.Length];
            for (int i = 0; i < numberStrings.Length; i++)
            {
                if (!double.TryParse(numberStrings[i], out numbers[i]))
                {
                    Console.WriteLine($"Invalid input: {numberStrings[i]}");
                    return;
                }
            }

            double geometricMean = Math.Pow(numbers.Aggregate((a, b) => a * b), 1.0 / numbers.Length);

            double harmonicMean = numbers.Length / numbers.Sum(x => 1.0 / x);

            Console.WriteLine($"Geometric mean: {geometricMean}");
            Console.WriteLine($"Harmonic mean: {harmonicMean}");
        }
    }
}