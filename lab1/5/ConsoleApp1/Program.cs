class Program
{
    static void Main()
    {
        Console.WriteLine("Enter the line:");
        string inputstring = Console.ReadLine();

        Console.WriteLine("Select an action:");
        Console.WriteLine("a) Sort words alphabetically and output the last characters");
        Console.WriteLine("b) Raise the case of the first letter and lower the case of the last letter in each word(the minimum word length is 2 letters)");
        Console.WriteLine("c) Count the number of occurrences of a given word");
        Console.WriteLine("d) Replace the penultimate word");
        Console.WriteLine("e) Find the k-th word starting with a capital letter");

        char choice = Console.ReadKey().KeyChar;
        Console.WriteLine();

        switch (choice)
        {
            case 'a':
                SortAndPrintLastCharacters(inputstring);
                break;
            case 'b':
                ModifyCase(inputstring);
                break;
            case 'c':
                CountOccurrences(inputstring);
                break;
            case 'd':
                ReplaceSecondToLastWord(inputstring);
                break;
            case 'e':
                FindKthCapitalizedWord(inputstring);
                break;
            default:
                Console.WriteLine("Wrong choice.");
                break;
        }
    }

    static void SortAndPrintLastCharacters(string input)
    {
        string[] words = input.Split(' ');
        Array.Sort(words);
        string result = new string(words.Select(w => w[w.Length - 1]).ToArray());
        Console.WriteLine(result);
    }

    static void ModifyCase(string input)
    {
        string[] words = input.Split(' ');
        for (int i = 0; i < words.Length; i++)
        {
            string word = words[i];
            if (word.Length > 0)
            {
                char firstChar = char.ToUpper(word[0]);
                char lastChar = char.ToLower(word[word.Length - 1]);
                words[i] = firstChar + word.Substring(1, word.Length - 2) + lastChar;
            }
        }
        string result = string.Join(" ", words);
        Console.WriteLine(result);
    }

    static void CountOccurrences(string input)
    {
        Console.WriteLine("Enter the word to count:");
        string wordToCount = Console.ReadLine();
        int count = input.Split(' ').Count(w => w.Equals(wordToCount, StringComparison.OrdinalIgnoreCase));
        Console.WriteLine($"Word {wordToCount} occurs {count} time.");
    }

    static void ReplaceSecondToLastWord(string input)
    {
        Console.WriteLine("Enter a new word:");
        string newWord = Console.ReadLine();

        string[] words = input.Split(' ');
        if (words.Length >= 2)
        {
            words[words.Length - 2] = newWord;
            string result = string.Join(" ", words);
            Console.WriteLine(result);
        }
        else
        {
            Console.WriteLine("The string does not contain enough words to replace.");
        }}

    static void FindKthCapitalizedWord(string input)
    {
        Console.WriteLine("Enter the number k:");
        int k = int.Parse(Console.ReadLine());

        string[] words = input.Split(' ');
        int count = 0;
        foreach (string word in words)
        {
            if (char.IsUpper(word[0]))
            {
                count++;
                if (count == k)
                {
                    Console.WriteLine($"k a word starting with a capital letter: {word}");
                    return;
                }
            }
        }
        Console.WriteLine("There is no single word starting with a capital letter in the line.");
    }
}