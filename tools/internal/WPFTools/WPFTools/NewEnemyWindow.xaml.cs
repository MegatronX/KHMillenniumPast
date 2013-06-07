using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;

using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WPFTools
{
    /// <summary>
    /// Interaction logic for NewEnemyWindow.xaml
    /// </summary>
    public partial class NewEnemyWindow : Window
    {
        bool Eject = false;
        bool AddedToDoc = false;
        XmlDocument parentDoc;
        Editor parentEditor;
        XmlElement enemyEle;
        public XmlElement NewEnemyElement 
        { 
            get { return enemyEle; } 
            set { enemyEle = value; } 
        }
        public NewEnemyWindow(XmlDocument doc, Editor editor)
        {
            NewEnemyElement = doc.CreateElement("Enemy");
            NewEnemyElement.SetAttribute("name", "");
            NewEnemyElement.SetAttribute("displayname", "");
            NewEnemyElement.SetAttribute("type", "");
            doc.DocumentElement.AppendChild(NewEnemyElement);
            Eject = true;
            parentDoc = doc;
            parentEditor = editor;
            InitializeComponent();

        }
        public NewEnemyWindow(XmlElement templateEnemy, Editor editor)
        {
            parentEditor = editor;
            try
            {
                NewEnemyElement = (XmlElement)templateEnemy.CloneNode(true);
                templateEnemy.ParentNode.AppendChild(NewEnemyElement);
                Eject = true;
                parentDoc = NewEnemyElement.OwnerDocument;


            }
            catch
            {
                Console.Out.WriteLine("Failed to receive an xmlelement");
            }
            InitializeComponent();


        }
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            if (Eject)
            {
                enemyEle.ParentNode.RemoveChild(enemyEle);
                Eject = false;
            }
            this.DialogResult = false;
        }

        private void AddInstanceButton_Click(object sender, RoutedEventArgs e)
        {
            NewEnemyInstanceWindow instWindow = new NewEnemyInstanceWindow(this.NewEnemyElement);
            var helper = new WindowInteropHelper(instWindow);
            helper.Owner = new WindowInteropHelper(this).Handle;
            bool? res = instWindow.ShowDialog();
            if (res != null && (bool)res)
            {

            }
            else
            {
               // MessageBox.Show("Did not add new enemy instance");
            }
            /*
             * NewEnemyWindow eneWindow = new NewEnemyWindow();
            var helper = new WindowInteropHelper(eneWindow);
            helper.Owner = new WindowInteropHelper(this).Handle;
            bool? res = eneWindow.ShowDialog();
            if (res != null && (bool)res)
            {
            }
            else
            {
                MessageBox.Show("Did not add new enemy");
            }
             */
        }
        private void PrepXMLNode()
        {

        }
        private void SaveXMLNode()
        {
            Eject = false;
            this.DialogResult = true;
            this.Close();
        }
        private void SaveNewEnemyButton_Click(object sender, RoutedEventArgs e)
        {
            var nameComp = EnemyNameTextBox.Text;
            if (nameComp != null && nameComp != string.Empty)
            {
                if (parentEditor != null)
                {
                    foreach (var item in parentEditor.EnemyListBox.Items)
                    {
                        if (item is XmlElement)
                        {
                            XmlElement xmlele = (XmlElement)item;
                            if (this.NewEnemyElement != item && xmlele.GetAttribute("name") == nameComp)
                            {
                                MessageBox.Show("An enemy with name " + nameComp + " already exists. Please select a different name");
                                return;
                            }

                        }
                    }
                    PrepXMLNode();
                    SaveXMLNode();
                    // Making new node

                }
            }
            else
            {
                MessageBox.Show("The enemy name is invalid!");
            }

        }

        private void DeleteInstance_Click(object sender, RoutedEventArgs e)
        {
            var item = ActiveEnemyInstances.SelectedItem;
            if (item != null && item is XmlElement)
            {
                var xmlItem = (XmlElement)item;
                if (MessageBox.Show("Are you sure you want to delete the level " + xmlItem.GetAttribute("level") + " instance?", "Confirm Deleteion", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    xmlItem.ParentNode.RemoveChild(xmlItem);
                }
            }
        }

        private void AddNewEnemyWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (Eject)
            {
                enemyEle.ParentNode.RemoveChild(enemyEle);
                Eject = false;
            }
        }

        private void AddClassButton_Click(object sender, RoutedEventArgs e)
        {
            var AvailableClass = AvailableEnemyClassesList.SelectedItem;
            if (AvailableClass != null && AvailableClass is XmlAttribute)
            {
                var dc = CurrentEnemyClassesList.DataContext;
                if (dc != null && dc is XmlElement)
                {
                    XmlElement enEle = (XmlElement)dc;
                    var classesEle = enEle.GetElementsByTagName("Classes");
                    if (classesEle.Count < 1)
                    {
                        enEle.PrependChild(enEle.OwnerDocument.CreateElement("Classes"));
                        classesEle = enEle.GetElementsByTagName("Classes");
                    }
                    //check is class already added
                    var check = classesEle[0].SelectNodes(((XmlAttribute)AvailableClass).Value);
                    if (check.Count == 0)
                    {
                        classesEle[0].AppendChild(((XmlAttribute)AvailableClass).OwnerElement.Clone());
                    }
                    
                }
            }
        }

        private void RemoveClassButton_Click(object sender, RoutedEventArgs e)
        {
            var RemovalClass = CurrentEnemyClassesList.SelectedItem as XmlAttribute;
            if (RemovalClass != null)
            {
                RemovalClass.OwnerElement.ParentNode.RemoveChild(RemovalClass.OwnerElement);
            }
        }
    }
}
