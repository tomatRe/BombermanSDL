using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapGenerator
{
    class MapGenerator
    {
        static void Main(string[] args)
        {
            Console.Write("Map size X: ");
            int sizex = Convert.ToInt32(Console.ReadLine());

            Console.Write("Map size Y: ");
            int sizey = Convert.ToInt32(Console.ReadLine());

            Console.Write("Border radious: ");
            int borderRadious = Convert.ToInt32(Console.ReadLine());

            Console.Write("Name: ");
            string name = Console.ReadLine();

            if (!File.Exists(name))
            {
                int[,] map = new int[sizex, sizey];

                for (int x = 0; x < sizex; x++)
                {
                    string line = "";

                    for (int y = 0; y < sizey; y++)
                    {
                        if (x < borderRadious || y < borderRadious || x >= (sizex-borderRadious) || y >= (sizey - borderRadious))
                        {
                            map[x, y] = 1;
                        }
                        else
                        {
                            map[x, y] = 0;
                        }

                        line += map[x, y];
                    }

                    using (StreamWriter sw = File.AppendText(name))
                    {
                        sw.WriteLine(line);
                    }
                }
            }
        }
    }
}
