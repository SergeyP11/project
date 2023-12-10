/*
Напишите две функции для поиска всех корней кубического уравнения
двумя разными способами: с помощью формулы Кордано и без неё.
Результат вычислений возвращайте как возвращаемое значение функции.
Сравните полученные результаты.

Пример 6 -5 -5 4
*/
class Program
{
    static void Main()
    {
        Console.WriteLine("Enter the parameters of the cubic equation a*x^3+b*x^2+c*x+d=0 :");
        Console.Write("a=");
        double a =Convert.ToDouble(Console.ReadLine());
        Console.Write("b=");
        double b = Convert.ToDouble(Console.ReadLine());
        Console.Write("c=");
        double c = Convert.ToDouble(Console.ReadLine());
        Console.Write("d=");
        double d = Convert.ToDouble(Console.ReadLine());
        Console.WriteLine("Method Kardano:");
        int tip = 0;
        double p1 = 0, p2 = 0, p3 = 0;
        MethodKardano(a, b, c, d, ref tip, ref p1, ref p2, ref p3);
        if (tip==1)
         Console.WriteLine("type=1. One real and two complex conjugate roots: x1={0} x2={1} x3={2}", p1, p2, p3);
        else
            Console.WriteLine("Real roots: тип={0} \np1={1} \np2={2} \np3={3}", tip, p1, p2, p3);
        double[] root = Method(a, b, c, d);
        Console.WriteLine("\nAlternative method:");
        int len = root.Length;
        if (len > 0) 
         Console.WriteLine("\nRoot 1: {0}", root[0]);
        if (len>1)
         Console.WriteLine("Root 2: {0}", root[1]);
        if (len>2)
         Console.WriteLine("Root 3: {0}", root[2]);
    }

    static void MethodKardano(double a, double b, double c, double d, ref int tip, ref double p1, ref double p2, ref double p3)
    {
        double eps = 1E-14;
        double p = (3 * a * c - b * b) / (3 * a * a);
        double q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);
        double det = q * q / 4 + p * p * p / 27;
        if (Math.Abs(det) < eps)
            det = 0;
        if (det > 0)
        {
            // один вещественный, два комплексных корня
            tip = 1;
            double u = -q / 2 + Math.Sqrt(det);
            u = Math.Exp(Math.Log(u) / 3);
            double yy = u - p / (3 * u);
            p1 = yy - b / (3 * a); // первый корень
            p2 = -(u - p / (3 * u)) / 2 - b / (3 * a);
            p3 = Math.Sqrt(3) / 2 * (u + p / (3 * u));
        }
        else
        {
            if (det < 0)
            {
                // три вещественных корня
                tip = 2;
                double fi;
                if (Math.Abs(q) < eps) // q=0
                    fi = Math.PI / 2;
                else
                {
                    if (q < 0) // q<0
                    fi = Math.Atan(Math.Sqrt(-det) / (-q / 2));
                    else // q<0
                    fi = Math.Atan(Math.Sqrt(-det) / (-q / 2)) + Math.PI;
                }
                double r = 2 * Math.Sqrt(-p / 3);
                p1 = r * Math.Cos(fi / 3) - b / (3 * a);
                p2 = r * Math.Cos((fi + 2 * Math.PI) / 3) - b / (3 * a);
                p3 = r * Math.Cos((fi + 4 * Math.PI) / 3) - b / (3 * a);
            }
            else // det=0
            {
                if (Math.Abs(q) < eps)
                {
                    tip = 4; // 3-х кратный 
                    p1 = -b / (3 * a); 
                    p2 = -b / (3 * a);
                    p3 = -b / (3 * a);
                }
                else
                {
                    tip = 3; // один и два кратных
                    double u = Math.Exp(Math.Log(Math.Abs(q)/2)/ 3);
                    if (q < 0)
                    u = -u;
                    p1 = -2 * u - b / (3 * a);
                    p2 = u - b / (3 * a);
                    p3 = u - b / (3 * a);
                }
            }
        }
    }

    public static double[] Dis(double a, double b, double c)
    {
        double eps=1E-14;
        double dis = b * b - 4 * a * c;
        if (dis>eps)
        {
            double x1 = (-b + Math.Sqrt(dis)) / (2 * a);
            double x2 = (-b - Math.Sqrt(dis)) / (2 * a);
            return new[]
            {
                x1,x2
            };
        }
        else if (dis == 0)
        {
            double x1 = -b / (2 * a);
            double x2 = x1;
            return new[]
            {
                x1,x2
            };
        }
        else return new double [] { }; 
    }

    static double[] Method(double a, double b, double c, double d)
    {
       if (Math.Abs(a) < 1e-14)
        {
            return Dis(b, c, d);
        }
        b /= a;
        c /= a;
        d /= a;
        double q = (3 * c - b * b) / 9;
        double r = (9 * b * c - 27 * d - 2 * b * b * b) / 54;
        double dis = q * q * q + r * r;
        if (dis > 0)
        {
            double s = Math.Sign(r + Math.Sqrt(dis)) * Math.Pow(Math.Abs(r + Math.Sqrt(dis)), 1.0 / 3.0);
            double t = Math.Sign(r - Math.Sqrt(dis)) * Math.Pow(Math.Abs(r - Math.Sqrt(dis)), 1.0 / 3.0);
            double x1 = -b / 3 + (s + t);
            double x2 = (-b / 3 - (s + t) / 2) + Math.Sqrt(3) * (s - t) / 2;
            double x3 = x2 - Math.Sqrt(3) * (s - t) / 2;
            return new double[]
            {
                x1,x2,x3
            };
        }
        else if (dis == 0)
        {
            double ri = Math.Pow(Math.Abs(r), 1.0 / 3.0);
            double x1 = -b / 3 + 2 * r;
            double x2 = -b / 3 - r;
            double x3 = x1;
            return new double[]
            {
                x1,x2,x3
            };
        }
        else
        {
            double theta = Math.Acos(r / Math.Sqrt(-(q * q * q)));
            double x1 = -b / 3 + 2 * Math.Sqrt(-q) * Math.Cos(theta / 3);
            double x2 = -b / 3 + 2 * Math.Sqrt(-q) * Math.Cos((theta + 2 * Math.PI) / 3);
            double x3 = -b / 3 + 2 * Math.Sqrt(-q) * Math.Cos((theta + 4 * Math.PI) / 3);
            return new double[]
            {
                x1,x2,x3
            };
        } 
    }
}