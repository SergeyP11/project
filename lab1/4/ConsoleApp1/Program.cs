class Program
{
    static void Main()
    {
        Console.Write("\nEnter a decimal fraction (the fractional part is separated by commas):");
        double decimalFraction = double.Parse(Console.ReadLine());

        Console.Write("\nEnter the base of the number system from 2 to 36: ");
        int k = int.Parse(Console.ReadLine());

        string result = ConvertDecimalFractionToBaseK(decimalFraction, k);
        Console.WriteLine($"\nResult: {result}");
    }

    static string ConvertDecimalFractionToBaseK(double decimalFraction, int k)
    {
        int wholePart = (int)decimalFraction;
        double fractionalPart = decimalFraction - wholePart;

        string result = ConvertWholePartToBaseK(wholePart, k) + ".";
        int precision = 10; // количество знаков после запятой для определения периодической части

        for (int i = 0; i < precision; i++)
        {
            fractionalPart *= k;
            int digit = (int)fractionalPart;
            result += digit;
            fractionalPart -= digit;

            if (fractionalPart == 0)
            {
                break;
            }
        }

        return result;
    }

    static string ConvertWholePartToBaseK(int wholePart, int k)
    {
        string result = "";
        while (wholePart > 0)
        {
            int remainder = wholePart % k;
            char digitChar = (char)(remainder < 10 ? remainder + '0' : remainder + 'A' - 10);
            result = digitChar + result;
            wholePart /= k;
        }
        return result == "" ? "0" : result;
    }
}
