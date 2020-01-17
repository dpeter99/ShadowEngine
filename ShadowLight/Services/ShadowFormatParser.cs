using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Services
{
    public static class ShadowFormatParser
    {
        public static Element LoadFile(string path)
        {
            //TODO: check if file exists
            System.IO.FileStream stream = new FileStream(path, FileMode.Open);


            return LoadFile(stream);
        }


        public static Element LoadFile(Stream stream)
        {


            StreamReader reader = new StreamReader(stream);

            //The current node that we are building
            var context = new Element();

            //Top level Element
            Element basElement = context;

            //The new node that will be a child of the context
            var current = new Element();


            var version = ReadFormatHeader(reader);

            bool readingString = false;

            string buffer = "";
            int c;
            while (!reader.EndOfStream)
            {
                c = reader.Read();

                if (c == ':')
                {
                    //The stuff in the buffer is a parameter name
                    if (!readingString)
                    {
                        DebugWrite("Name: " + buffer+"\n");
                        current.name = buffer;
                        buffer = "";
                    }
                    else
                    {
                        buffer += (char) c;
                    }
                }
                else if (c == '{')
                {
                    if (!readingString)
                    {
                        //Start of a new block
                        current.isBlock = true;
                        current.parent = context;
                        context.properties[current.name] = current;
                        context = current;

                        current = new Element();
                    }
                }
                else if (c == ',')
                {
                    if (!readingString)
                    {
                        // End of a property
                        //The content of the buffer is the value
                        Console.WriteLine(" Value: " + buffer);
                        current.value = buffer;
                        current.parent = context;
                        current.isBlock = false;
                        buffer = "";

                        context.properties[current.name] = current;

                        current = new Element();
                    }
                    else
                    {
                        buffer += (char) c;
                    }
                }
                else if (c == '}')
                {
                    if (readingString)
                    {
                        //End of a string
                        //The content of the buffer is the string
                        Console.WriteLine("Value: " + buffer);
                        current.value = buffer;
                        current.parent = context;
                        current.isBlock = false;
                        buffer = "";

                        context.properties[current.name] = current;

                        current = new Element();

                        readingString = false;
                    }
                    else
                    {
                        // End of a block
                        context = context.parent;
                    }
                }
                else if (c == '@' && reader.Peek() == '{')
                {
                    readingString = true;
                    reader.Read();
                }
                else
                {
                    if (!Char.IsWhiteSpace((char) c) || readingString)
                    {
                        buffer += (char) c;
                    }
                }

            }

            return basElement;
        }

        public static (int mayor, int minor, int patch) ReadFormatHeader(StreamReader reader)
        {
            var line = reader.ReadLine();
            var parts = line.Split('_');
            if (parts[0] == "ShadowFormat")
            {
                int mayor = int.Parse(parts[1]);
                int minor = int.Parse(parts[2]);
                int patch = int.Parse(parts[3]);
                return (mayor, minor, patch);
            }

            return (0, 0, 0);
        }

        private static int indent_count = 0;
        static void DebugWrite(string text)
        {
            string indent = "";
            for (int i = 0; i < indent_count; i++)
            {
                indent += "\t";
            }

            Console.WriteLine(indent + text);
        }

    public class Element
        {
            public Element parent;

            public string name;

            public bool isBlock;

            public string value;

            public Dictionary<string, Element> properties = new Dictionary<string, Element>();

            public int GetIntProperty(string key)
            {
                return int.Parse(properties[key].value);
            }

            public string GetStringProperty(string key)
            {
                return properties[key].value;
            }
        }
    }
}
