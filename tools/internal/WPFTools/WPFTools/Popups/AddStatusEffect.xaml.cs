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

namespace WPFTools.Popups
{
    /// <summary>
    /// Interaction logic for AddStatusEffect.xaml
    /// </summary>
    public partial class AddStatusEffect : Window
    {
        bool Eject = false;
        XmlElement seRoot;
        XmlElement newSE;
        string TemplateName;
        public XmlElement SERoot
        {
            get { return seRoot; }
            set { seRoot = value; }
        }
        public XmlElement NewSE
        {
            get { return newSE; }
            set { newSE = value; }
        }
        public AddStatusEffect(XmlElement rootSE, string templateName)
        {
            seRoot = rootSE;
            TemplateName = templateName;
            NewSE = MakeSETemplate(rootSE.OwnerDocument);
            rootSE.AppendChild(NewSE);
            Eject = true;
            InitializeComponent();
        }

        private XmlElement MakeSETemplate(XmlDocument doc)
        {
            XmlElement seTemp = doc.CreateElement(TemplateName);
            seTemp.SetAttribute("name", "Default SE");
            seTemp.SetAttribute("value", "0");

            return seTemp;
        }

        private void AddStatusEffect_Click(object sender, RoutedEventArgs e)
        {
            if (AlreadyExists(AddStatusEffectNameBox.Text, 1))
            {
                MessageBox.Show("Status Effect with name " + AddStatusEffectNameBox.Text + " already exists. Please rename the status effect or cancel");
            }
            else
            {
                Eject = false;
                this.DialogResult = true;
            }
            //this.Close();
        }
        bool AlreadyExists(string name, int tolerance)
        {
            int count = 0;
            if (SERoot != null)
            {
                foreach (XmlNode node in SERoot.ChildNodes)
                {
                    if (name == node.Attributes.GetNamedItem("name").Value)
                    {
                        ++count;
                        if (count > tolerance)
                            return true;
                    }

                }
            }
            return false;
        }
        private void CancelAddStatusEffect_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;
        }

        

        private void AddStatusEffectWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (Eject && NewSE != null)
            {
                NewSE.ParentNode.RemoveChild(NewSE);
                Eject = false;
            }
        }
    }
}
