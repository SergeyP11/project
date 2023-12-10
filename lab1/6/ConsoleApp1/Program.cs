public delegate double EquationDelegate(double x);

public class DichotomyMethod
{
    public static double FindRoot(double a, double b, EquationDelegate equation, double precision)
    {
        if (equation(a) * equation(b) >= 0)
        {
            throw new ArgumentException("The function values at the interval endpoints must have different signs");
        }

        while ((b - a) >= precision)
        {
            double mid = (a + b) / 2;
            if (equation(mid) == 0.0)
            {
                return mid;
            }
            else if (equation(mid) * equation(a) < 0)
            {
                b = mid;
            }
            else
            {
                a = mid;
            }
        }

        return (a + b) / 2;
    }
}

public class Program
{
    public static void Main()
    {
        // Пример x^2 - 4 = 0 на интервале от 1 до 3 с точностью 0.001
        EquationDelegate equation1 = x => x * x - 4;
        double root1 = DichotomyMethod.FindRoot(1, 3, equation1, 0.001);
        Console.WriteLine("Root of the equation x^2 - 4 = 0 on the interval [1, 3] with precision 0.001: " + root1);

        // Пример sin(x) = 0 на интервале от 1 до 4 с точностью 0.001
        EquationDelegate equation2 = Math.Sin;
        double root2 = DichotomyMethod.FindRoot(1, 4, equation2, 0.001);
        Console.WriteLine("Root of the equation sin(x) = 0 on the interval [1, 4] with precision 0.0001: " + root2);
    }
}
