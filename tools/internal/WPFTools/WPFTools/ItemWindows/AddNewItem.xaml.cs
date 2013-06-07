using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WPFTools.ItemWindows
{
    /// <summary>
    /// Interaction logic for AddNewItem.xaml
    /// </summary>
    public partial class AddNewItem : Window
    {
        bool Eject = false;
        bool AddedToDoc = false;
        XmlElement itemRoot;
        Editor parentEditor;
        XmlElement itemEle;

        public XmlElement NewItemElement
        {
            get { return itemEle; }
            set { itemEle = value; }
        }

        public AddNewItem(XmlElement itemR, Editor editor)
        {
            itemRoot = itemR;
            parentEditor = editor;
            Eject = true;
            NewItemElement = MakeXMLItemTemplate(itemR.OwnerDocument);

            //NewItemElement.AppendChild();
            itemRoot.AppendChild(NewItemElement);
            InitializeComponent();
        }

        public AddNewItem()
        {
            InitializeComponent();
        }

        private XmlElement MakeXMLItemTemplate(XmlDocument doc)
        {

            XElement template = new XElement("Item", new XAttribute("name", "Bad Item"), new XAttribute("value", "0"),
                                                new XElement("Family", new XAttribute("value", "Invalid")),
                                                new XElement("Classes"),
                                                new XElement("Description", new XAttribute("value", "Bad Item")),
                                                new XElement("Components"),
                                                new XElement("Flags")
                                            );

            using (var xmlRead = template.CreateReader())
            {
                return (XmlElement)doc.ReadNode(xmlRead);
            }
        }

        private void SaveNewItem()
        {
            this.DialogResult = true;
            this.Close();
        }

        private void SaveNewButtonClass_Click(object sender, RoutedEventArgs e)
        {
            var name = ItemName.Text;
            if (name != null && name != String.Empty && name != "Bad Item")
            {
                var eles = itemRoot.SelectNodes("Item");
                foreach (XmlNode element in eles)
                {
                    if (element != this.NewItemElement)
                    {
                        if (((XmlElement)element).GetAttribute("name") == name)
                        {
                            MessageBox.Show("An item with name " + name + " already exists. You must use a different name");
                            return;
                        }
                    }
                }
                Eject = false;
                SaveNewItem();
            }
            else
            {
                MessageBox.Show("Can not add an item with name " + name);
            }
        }

        private void CancelNewItemClass_Click(object sender, RoutedEventArgs e)
        {
            if (Eject)
            {
                itemEle.ParentNode.RemoveChild(itemEle);
                Eject = false;
            }
            this.DialogResult = false;
        }

        private void AddNewItemWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (itemEle != null && itemEle.ParentNode != null && Eject)
            {
                itemEle.ParentNode.RemoveChild(itemEle);
                Eject = false;
            }
        }
    }
}
