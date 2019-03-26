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
            this.properties.Add(element.name,element);
        }

    }


    public static class ShadowFileFormat
    {
        public static void WriteFile(ShadowFileElement root, string path)
        {
            StreamWriter writer = new StreamWriter(path);


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
    }
}
