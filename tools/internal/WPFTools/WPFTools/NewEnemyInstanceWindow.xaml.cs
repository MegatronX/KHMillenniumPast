using System;
using System.Xml;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WPFTools
{
    /// <summary>
    /// Interaction logic for NewEnemyInstanceWindow.xaml
    /// </summary>
    public partial class NewEnemyInstanceWindow : Window
    {
        bool Eject = false;
        XmlElement enemyElement;
        XmlElement enemyInstanceEle;
        public XmlElement NewEnemyInstanceElement { get { return enemyInstanceEle; } set { enemyInstanceEle = value; } }
        //New Instance constructor
        public NewEnemyInstanceWindow(XmlElement enemyelement)
        {
            enemyElement = enemyelement;
            NewEnemyInstanceElement = MakeXmlEnemyInstanceTemplate(enemyElement.OwnerDocument);
            enemyElement.AppendChild(NewEnemyInstanceElement);
            Eject = true;
            InitializeComponent();
        }
        //Need to add a view an instance constructor
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            enemyElement.RemoveChild(NewEnemyInstanceElement);
            Eject = false;
            this.DialogResult = false;
        }

        private XmlElement MakeXmlEnemyInstanceTemplate(XmlDocument doc)
        {
           
            XElement template = new XElement("EnemyInstance", new XAttribute("level", "0"),
                                                new XElement("Description", new XAttribute("value", "0")),
                                                new XElement("Classes"),
                                                new XElement("Stats", new XAttribute("HP", "1"), new XAttribute("MP", "0"), new XAttribute("SP", "0"), new XAttribute("Strength", "0"), new XAttribute("Vitality", "0"), new XAttribute("Magic", "0"), new XAttribute("Spirit", "0"), new XAttribute("Skill", "0"), new XAttribute("Speed", "0"), new XAttribute("Evasion", "0"), new XAttribute("MgEvasion", "0"), new XAttribute("Accuracy", "0"), new XAttribute("Luck", "0")),
                                                new XElement("StatusResistances"),
                                                new XElement("ElementalEffectiveness"),
                                                new XElement("LootTable"),
                                                new XElement("DropTable"),
                                                new XElement("AIScript"),
                                                new XElement("Flags"));            
            using (var xmlRead = template.CreateReader())
            {
                return (XmlElement)doc.ReadNode(xmlRead);
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (enemyElement != null && Eject)
            {
                enemyElement.RemoveChild(NewEnemyInstanceElement);
                Eject = false;
            }
        }
        private void SaveEnemyInstance()
        {
            this.DialogResult = true;
            this.Close();
        }
        private void SaveEnemyInstance_Click(object sender, RoutedEventArgs e)
        {
            var levelComp = EnemyLevelBox.Text;
            if (levelComp != null && levelComp != string.Empty)
            {
                levelComp = levelComp.Trim();
                int levelCheck = 0;
                if (Int32.TryParse(levelComp, out levelCheck) && levelCheck >= 0 && levelCheck <= 100)
                {
                    var eles = enemyElement.SelectNodes("EnemyInstance");
                    
                    foreach (XmlNode element in eles)
                    {
                        if (element != this.NewEnemyInstanceElement)
                        {
                            int sourceLevel;
                            if (Int32.TryParse(((XmlElement)element).GetAttribute("level"), out sourceLevel))
                            {
                                if (sourceLevel == levelCheck)
                                {
                                    MessageBox.Show("An enemy instance with the level " + sourceLevel + " already exists. You must use a different level");
                                    return;
                                }

                            }
                        }
                    }

                    Eject = false;
                    SaveEnemyInstance();
                }
                else
                {
                    MessageBox.Show("The entered level was not a valid number. Please use an integer value between 0 and 100");
                }
            }
            else
            {
                MessageBox.Show("The level enterted is invalid text");
            }
        }
    }
}
