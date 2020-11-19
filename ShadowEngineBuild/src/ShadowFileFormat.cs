using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild
{
    public class ShadowFileElement
    {
        public ShadowFileElement parent;

        public string name;

        public bool isBlock;

        public string value;

        
        public Dictionary<string, ShadowFileElement> properties= new Dictionary<string, ShadowFileElement>();

        public void AddProperty(string name, string value)
        {
            var a = new ShadowFileElement();
            a.name = name;
            a.value = value;
            a.isBlock = false;

            this.properties.Add(a.name ,a);
        }

        public void AddProperty(ShadowFileElement element)
        {
            this.isBlock = true; //TODO: I think this is correct but i didn't touch this code in a long while :/
            this.properties.Add(element.name,element);
        }

        public int GetIntProperty(string key)
        {
            return int.Parse(properties[key].value);
        }

        public string GetStringProperty(string key)
        {
            return properties[key].value;
        }
    }


    public static class ShadowFileFormat
    {
        public static void WriteFile(ShadowFileElement root, string path)
        {
            StreamWriter writer = new StreamWriter(path);
            writer.WriteLine("ShadowFileFormat_1_0_0");

            int depth = 0;
            WriteElement(writer,root,ref depth);

            writer.Close();
        }

        public static void WriteElement(StreamWriter w , ShadowFileElement e,ref int depth)
        {
            string head = (e.name + (e.isBlock ? ":{" : ":"));
            head = head.PadLeft(depth + head.Length, '\t');
            w.Write(head);
            if (e.isBlock)
            {
                depth += 1;
                w.WriteLine();
                foreach (var property in e.properties)
                {
                    WriteElement(w,property.Value,ref depth);
                }
                w.WriteLine(("}").PadLeft(depth,'\t'));
                depth -= 1;
            }
            else
            {
                w.WriteLine(e.value+",");
            }

            
        }

        public static ShadowFileElement LoadFile(string path)
        {
            //TODO: check if file exists
            System.IO.FileStream stream = new FileStream(path, FileMode.Open);


            return LoadFile(stream);
        }


        public static ShadowFileElement LoadFile(Stream stream)
        {


            StreamReader reader = new StreamReader(stream);

            //The current node that we are building
            var context = new ShadowFileElement();

            //Top level Element
            ShadowFileElement basElement = context;

            //The new node that will be a child of the context
            var current = new ShadowFileElement();


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
                        //DebugWrite("Name: " + buffer + "\n");
                        current.name = buffer;
                        buffer = "";
                    }
                    else
                    {
                        buffer += (char)c;
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

                        current = new ShadowFileElement();
                    }
                }
                else if (c == ',')
                {
                    if (!readingString)
                    {
                        // End of a property
                        //The content of the buffer is the value
                        //Console.WriteLine(" Value: " + buffer);
                        current.value = buffer;
                        current.parent = context;
                        current.isBlock = false;
                        buffer = "";

                        context.properties[current.name] = current;

                        current = new ShadowFileElement();
                    }
                    else
                    {
                        buffer += (char)c;
                    }
                }
                else if (c == '}')
                {
                    if (readingString)
                    {
                        //End of a string
                        //The content of the buffer is the string
                        //Console.WriteLine("Value: " + buffer);
                        current.value = buffer;
                        current.parent = context;
                        current.isBlock = false;
                        buffer = "";

                        context.properties[current.name] = current;

                        current = new ShadowFileElement();

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
                    if (!Char.IsWhiteSpace((char)c) || readingString)
                    {
                        buffer += (char)c;
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
    }
}
