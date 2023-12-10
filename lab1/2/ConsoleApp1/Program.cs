// series сумма ряда
// equation уравнение
// limit предел
namespace ConstantsCalculation
{
    class Program
    {
        static void Main(string[] args)
        {
            double epsilon = 1E-3; //точность
            int rt = 100000000; //точность в виде количества операций (для циклов)

            // Calculate e
            double eSeries = ESeries(rt);
            double eEquation = EEquation(epsilon);
            double eLimit = ELimit(rt, epsilon);
            Console.WriteLine($"\ne: Series {eSeries}" + $" Equation {eEquation}" + $" Limit {eLimit}");

            // Calculate π
            double piSeries = PiSeries(epsilon);
            double piEquation = PiEquation(epsilon);
            double piLimit = PiLimit(epsilon, rt);

            Console.WriteLine($"\nπ: Series={piSeries}, Equation={piEquation}, Limit={piLimit}");

            // Calculate ln(2)
            double ln2Series = Ln2Series(epsilon);
            double ln2Equation = Ln2Equation(epsilon);
            double ln2Limit = Ln2Limit(epsilon);
            Console.WriteLine($"\nln2: Series={ln2Series}, Equation={ln2Equation}, Limit={ln2Limit}");

            // Calculate 2^1/2
            double Sqrt2Series = sqrt2Series(epsilon, rt);
            double Sqrt2Equation = sqrt2Equation(epsilon);
            double Sqrt2Limit = sqrt2Limit(epsilon);
            Console.WriteLine($"\nSqrt(2): Series={Sqrt2Series}, Equation={Sqrt2Equation}, Limit={Sqrt2Limit}");

            // Calculate γ
            // double gammaSeries = GammaSeries(epsilon);
            // double gammaEquation = GammaEquation(epsilon);
            double gammaSeries = 0;
            double gammaEquation = 0;
            double gammaLimit = GammaLimit(epsilon);
            Console.WriteLine($"\nγ: Series={gammaSeries}, Equation={gammaEquation}, Limit={gammaLimit}");
        }

        static double ESeries(int rt)
        {
            double e = 1;
            double factorial = 1;
            for (int n = 1; n <= rt; n++)
            {
                factorial *= n;
                e += 1 / factorial;
            }
            return e;
        }
        static double EEquation(double epsilon)
        {
            double x0 = 2.0; // Начальное приближение
            double xn = x0 - (Math.Log(x0) - 1) / (1 / x0);
            
            while (Math.Abs(xn - x0) > epsilon)
            {
                x0 = xn;
                xn = x0 - (Math.Log(x0) - 1) / (1 / x0);
            }
            
            return xn;

        }
        static double ELimit(double rt, double eps)
        {
            double e = 0;
            double limit = 0;
            for (int n = 1; n < rt; n++)
            {
                limit = Math.Pow((1 + (1.0 / n)), n);
                if (Math.Abs(limit - e) < eps)
                {
                    break;
                }
                e = limit;
            }
            return e;
        }
        static double PiSeries(double epsilon)
        {
            double series = 0;
            int n = 1;
            double member = 1.0;
            while (Math.Abs(member) > epsilon)
            {
                member = (double)Math.Pow(-1, n-1) /(2 * n - 1);
                series += member;
                n++;
            }
            return 4*series;
        }
        static double PiEquation(double epsilon)
        {
            double x = Math.PI;

            while (Math.Abs(Math.Cos(x) + 1.0) > epsilon) 
            {
                x -= (Math.Cos(x) + 1.0) / Math.Sin(x); 
            }

            return x;
        }
        static double PiLimit(double eps, int rt)
        {
            static int factorial(int n)
            { 
                int fact = 1;
                for (int i = 2; i <= n; i++)
                {
                    fact *= i;
                }
                return fact;
            }
            double prev = 0, cur = 1;
            for (int counter = 1; counter <= int.MaxValue && Math.Abs(cur - prev) > eps; counter++)
            {
                prev = cur;
                double num = Math.Pow(2, counter) * factorial(counter);
                double up = Math.Pow(num, 4);
                double num2 = factorial(counter * 2);
                double down = counter * Math.Pow(num2, 2);
                if (down > int.MaxValue)
                    break;
                cur = up/down;
                
            }
            return cur;
        }
        static double Ln2Series(double epsilon)
        {
            double series = 0;
            int n = 1;
            double member = 1.0;
            while (Math.Abs(member) > epsilon)
            {
                member = (double)Math.Pow(-1, n - 1) / n;
                series += member;
                n++;
            }
            return series;

        }
        static double Ln2Equation(double epsilon)
        {
            double x = 0.0;
            while (Math.Abs(Math.Exp(x) - 2.0) > epsilon) 
             {
                x -= (Math.Exp(x) - 2.0) / Math.Exp(x);
            }
            return x; 
        }
        static double Ln2Limit(double epsilon)
        {
            double prev = 0, cur = 2;
            for (int counter = 1; counter <= int.MaxValue && Math.Abs(cur - prev) > epsilon; counter++)
            {
                prev = cur;
                cur = counter * (Math.Pow(2, 1.0 / counter) - 1);
            }
            return cur;
        }
        static double sqrt2Series(double epsilon, int rt)
        {
            double product = 1.0;
            double term = 1.0;

            for (int k = 2; k<=rt ; k++)
            {
                term = Math.Pow(2, Math.Pow(2, -k));

                if (Math.Abs(term) < epsilon)
                {
                    break;
                }
                product *= term;
            }
            
            return product;
        }

        static double sqrt2Equation(double epsilon)
        {
            double x = 1.0;
            double x_prev;
            do
            {
                x_prev = x;
                x = x_prev - (x_prev * x_prev - 2) / (2 * x_prev); 
            } while (Math.Abs(x - x_prev) > epsilon);
            return x;
        }

        static double sqrt2Limit(double epsilon)
        {
            double prev = 0, current = -0.5;
            for (int counter = 1; counter <= int.MaxValue && Math.Abs(current - prev) > epsilon; counter++)
            {
                prev = current;
                current = prev - (Math.Pow(prev, 2) / 2) + 1;
            }
            return current;
        }


        // static double GammaSeries(double epsilon)
        // {
        //     
        // }

        // static double GammaEquation(double epsilon)
        // {
        //     
        // }

        static double GammaLimit(double epsilon)
        {
            double series = 0;
            double member; 
            double prev = 0;
            double cur = -0.5;

            static int factorial(int n)
            { 
                int fact = 1;
                for (int i = 2; i <= n; i++)
                {
                    fact *= i;
                }
                return fact;
            }
            for (int m = 1; m <= int.MaxValue && Math.Abs(cur - prev) > epsilon; m++)
            {
                if (cur != 0) 
                    prev = cur;
                int k = 1;
                while (k < m)
                {
                    double c = factorial(m) / (factorial(k) * factorial(m - k));
                    if (c <= 0)
                        break;
                    double fraction = Math.Pow(-1, k) / k;
                    double ln = Math.Log(factorial(k));
                    if (ln is double.NaN)
                        break;
                    member = c * fraction * ln;
                    series += member;
                    k++;
                }
                
                cur = series;
            }
            return cur;
        }
    }
}   