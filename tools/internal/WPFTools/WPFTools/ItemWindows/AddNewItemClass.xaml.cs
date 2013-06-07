using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

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
    /// Interaction logic for AddNewItemClass.xaml
    /// </summary>
    public partial class AddNewItemClass : Window
    {
        bool Eject = false;
        XmlElement allClassesRootElement;
        XmlElement newClassElement;
        public XmlElement AllClassesRootElement
        {
            get { return allClassesRootElement; }
            set { allClassesRootElement = value; }
        }
        public XmlElement NewClassElement
        {
            get { return newClassElement; }
            set { newClassElement = value; }
        }
        public AddNewItemClass(XmlElement RootAllClassesElement)
        {
            allClassesRootElement = RootAllClassesElement;
            newClassElement = RootAllClassesElement.OwnerDocument.CreateElement("Class");
            newClassElement.SetAttribute("value", "");// = "";//.Append(newClassElement.OwnerDocument.CreateAttribute("value"));
            allClassesRootElement.AppendChild(newClassElement);
            Eject = true;
            InitializeComponent();
        }

        private void CancelNewItemClass_Click(object sender, RoutedEventArgs e)
        {
            if (Eject)
            {
                newClassElement.ParentNode.RemoveChild(newClassElement);
                Eject = false;
            }
            this.Close();
        }

        private void AddNewItemClassWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (Eject)
            {
                newClassElement.ParentNode.RemoveChild(newClassElement);
                Eject = false;
            }
        }

        private void SaveNewButtonClass_Click(object sender, RoutedEventArgs e)
        {
            //Validate Name
            if (NewClassNameBox.Text != null && !NewClassNameBox.Text.Equals(string.Empty))
            {
                string newclass = NewClassNameBox.Text.Trim();
                foreach (XmlElement classDesc in allClassesRootElement.ChildNodes)
                {
                    string className = classDesc.GetAttribute("value");
                    if (className != null && !className.Equals(string.Empty))
                    {
                        if (className.Equals(newclass) && classDesc != this.newClassElement)
                        {
                            MessageBox.Show("A class with name " + newclass + " already exists. Please use a different name." );
                            return;
                        }
                    }
                }
                Eject = false;
                //this.DialogResult = true;
                this.Close();
            }
            else
            {
                MessageBox.Show("Invalid class name");
            }
        }
    }
}
