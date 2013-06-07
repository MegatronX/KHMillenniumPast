using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Linq;
using System.Runtime;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data;
using System.Xml;
using System.Xml.Xsl;
using WPFTools.Holders;

namespace WPFTools
{
    /// <summary>
    /// Interaction logic for Editor.xaml
    /// </summary>
    public partial class Editor : Window
    {
        static readonly Dictionary<string, string> StatDescriptors = new Dictionary<string, string>()
        {
            {"HP", "Hit Points\n A measure of the users reiliancy and ability to take hits. Higher HP makes the character better able to tank all forms of damage and is consumed for some attacks"},
            {"MP", "Magic Power\n A measure of the users magical energy, MP determines how much magic power is available for the player to use magic and skills"},
            {"SP", "Skill Power\n A measure of the amount of energy the character has available to perform special techniques."},
            {"Strength", "A measure of the players raw power, Strength is the primary determinant of the damage from normal attacks and many skills."},
            {"Vitality", "A measure of the player's resiliancy to physical attacks, Vitality acts to decrease the raw damage of most physical and some magical attacks"},
            {"Magic", "A measure of the users magic potency, Magic is the primary damage governer for most magic attacks"},
            {"Spirit", "Spirit reflects how severely a character is impacted by magic attacks"},
            {"Skill", "Skill acts as the primary damage governer on most skills"},
            {"Speed", "Speed detrmines how frequently the character is able to make a move"},
            {"Evasion", "Evasion determines how readily the character is able to avoid physical attacks"},
            {"MgEvasion", "Magic Evasion determines how readily the character is able to avoid magic based attacks"},
            {"Luck", "Determines how lucky the character is. The consequences of this stat are subtle, but in general, higher luck influences the Random Number Generator to provide results more favourable to the player"},
        };
        bool LoadingData = true;
        ActiveEnemyHolder ActiveEnemy = new ActiveEnemyHolder();
        DataSet EnemyDataSet = new DataSet();
        SortedDictionary<string, SortedDictionary<int, EnemyHolder>> EnemySet = new SortedDictionary<string, SortedDictionary<int, EnemyHolder>>();
        Dictionary<string, int> EnemyNameIDLookup = new Dictionary<string, int>();
        Dictionary<int, String> EnemyIDNameLookup = new Dictionary<int, String>();
        public Editor()
        {
            InitializeComponent();
            /*try
            {

                foreach (var ResVal in this.Resources.Values)
                {
                    if (ResVal is XmlDataProvider)
                    {
                        
                        XmlDataProvider xmlDP = (XmlDataProvider)ResVal;
                        string Source = xmlDP.Source.ToString();
                        if (Source.Contains("Enemies.xml"))
                        {
                            //string appPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().CodeBase);
                            //xmlDP.Source = new Uri(appPath + "Enemies.xml");
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                Console.Out.WriteLine("Could not find xml data provider. Exception: " + ex.Message);
            }*/
            //string appPath = System.IO.Path.GetDirectoryName(
         //System.Reflection.Assembly.GetExecutingAssembly().CodeBase);
           // EnemiesXML.Source = new Uri(appPath + @"\Enemies.xml");
            //Add Manual Event Handlers
            /*((INotifyCollectionChanged)EnemyListBox.Items).CollectionChanged += EnemyListBox_CollectionChanged;
            EnemyDataSet.ReadXmlSchema("Enemies.xsd");
            EnemyDataSet.ReadXml("Enemies.xml");
            if (EnemyDataSet.Tables.Count > 0)
            {
                for (int i = 0; i < EnemyDataSet.Tables[0].Rows.Count; ++i)
                {
                    var itemArr = EnemyDataSet.Tables[0].Rows[i].ItemArray;
                    string enemyName = itemArr[0].ToString();
                    EnemySet[enemyName] = new SortedDictionary<int, EnemyHolder>();
                    int ID = (int)itemArr[itemArr.Length - 1];
                    EnemyNameIDLookup[enemyName] = ID;
                    EnemyIDNameLookup[ID] = enemyName;
                }
                for (int i = 0; i < EnemyDataSet.Tables[1].Rows.Count; ++i)
                {
                    var itemArr = EnemyDataSet.Tables[1].Rows[i].ItemArray;
                    int enemyID = (int)itemArr[itemArr.Length - 1];
                    int level = 0;
                    if (Int32.TryParse(itemArr[0].ToString(), out level))
                    {
                        EnemySet[EnemyIDNameLookup[enemyID]][level] = new EnemyHolder();
                    }  
                }
            }*/
            
               /* for (int i = 0; i < EnemyDataSet.Tables.Count; ++i)
                {
                    for (int j = 0; j < EnemyDataSet.Tables[i].Rows.Count; ++j)
                    {
                        //EnemyDataSet.Tables[i].Rows.
                        var items = EnemyDataSet.Tables[i].Rows[j].ItemArray;
                        if (i == 0)
                            
                    }
                }*/
            /*foreach (var enemyset in EnemySet)
            {
                EnemyListBox.Items.Add(enemyset.Key);
            }
            SetUpBindings();*/
            LoadingData = false;
            SetUpExplicitEvents();
            LoadIntialDocs();
            InitiateShaderData();
            EnemyCountLabel.Content = EnemyListBox.Items.Count;
        }
        protected void LoadIntialDocs()
        {
            string CurrentDir = System.IO.Directory.GetCurrentDirectory();
            string itemsDB = System.Configuration.ConfigurationManager.AppSettings["InitialItemDB"];
            
            if (itemsDB != null && System.IO.File.Exists(itemsDB))
            {
                ItemsDBFile.Text = itemsDB;
                if (this.Resources.Contains("ItemDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ItemDB"];
                    xmlDP.Source = new Uri(itemsDB, UriKind.RelativeOrAbsolute);

                }
            }
            string enemiesDB = System.Configuration.ConfigurationManager.AppSettings["InitialEnemyDB"];
            if (enemiesDB != null && System.IO.File.Exists(enemiesDB))
            {
                EnemyDBFile.Text = enemiesDB;
                if (this.Resources.Contains("EnemyDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["EnemyDB"];
                    xmlDP.Source = new Uri(enemiesDB, UriKind.RelativeOrAbsolute);

                }
            }
            string actionDB = System.Configuration.ConfigurationManager.AppSettings["InitialActionDB"];
            if (actionDB != null && System.IO.File.Exists(actionDB))
            {
                bool cont = true;
                while (cont)
                {
                    XmlDocument doc = new XmlDocument();
                    doc.Load(actionDB);
                    XmlNodeList nodes = doc.SelectNodes("/Actions/*");
                    cont = false;
                }
                
                ActionDBFile.Text = actionDB;
                if (this.Resources.Contains("ActionDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ActionDB"];
                    xmlDP.Source = new Uri(actionDB, UriKind.RelativeOrAbsolute);
                }
            }
        }
        protected void SetUpExplicitEvents()
        {
            ((INotifyCollectionChanged)EnemyListBox.Items).CollectionChanged += EnemyListBox_CollectionChanged;
            ((INotifyCollectionChanged)ItemListBox.Items).CollectionChanged += ItemListBox_CollectionChanged;
            ((INotifyCollectionChanged)ActionListBox.Items).CollectionChanged += ActionListBox_CollectionChanged;
        }
        protected void SetUpBindings()
        {
            Binding binding = new Binding("Name");
            binding.Source = ActiveEnemy;
            //textBox1.SetBinding(TextBlock.TextProperty, binding);
        }
        private void LoadDefaults_Click(object sender, RoutedEventArgs e)
        {
            LoadIntialDocs();
        }
        #region Enemy Tab Region
        private void EnableCustomScript_Checked(object sender, RoutedEventArgs e)
        {
            if (EnableCustomScript.IsChecked != null)
            {
                EnemyScriptSource.IsEnabled = (bool)EnableCustomScript.IsChecked;
                EnemyScriptSource.IsReadOnly = !(bool)EnableCustomScript.IsChecked;
            }
        }
        private void EnemyListBox_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            EnemyCountLabel.Content = EnemyListBox.Items.Count;
            if (e.Action == NotifyCollectionChangedAction.Add)
            {
                
                
                EnemyListBox.ScrollIntoView(e.NewItems[0]);
            }
            /*else if (e.Action == NotifyCollectionChangedAction.Remove)
            {
                EnemyCountLabel.Content = EnemyListBox.Items.Count;
            }*/
        }
        private void EnemyListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //Clear Shown Data
            if (e.AddedItems.Count > 0)
            {
                if (e.AddedItems[0] is System.Xml.XmlElement)
                {
                    try
                    {
                        EnemyNameLabel.Content = ((System.Xml.XmlElement)e.AddedItems[0]).GetAttribute("name");
                    }
                    catch
                    {
                    }
                }
                else
                {
                    EnemyNameLabel.Content = e.AddedItems[0].ToString();
                }
            }
        }
        private void AddNewEnemyButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("EnemyDB"))
            {
                XmlDataProvider dataProv = (XmlDataProvider)this.Resources["EnemyDB"];
                if (dataProv.Document != null)
                {
                    NewEnemyWindow eneWindow = new NewEnemyWindow(dataProv.Document, this);
                    var helper = new WindowInteropHelper(eneWindow);
                    helper.Owner = new WindowInteropHelper(this).Handle;
                    bool? res = eneWindow.ShowDialog();
                    if (res != null && (bool)res)
                    {
                    }
                    else
                    {
                        //MessageBox.Show("Did not add new enemy");
                    }
                }
                else
                {
                    Console.Out.WriteLine("There is no valid Enemy XML file to add enemy to!");
                }
                
            }
            
        }
        private void AddNewEnemyInstanceButton_Click(object sender, RoutedEventArgs e)
        {
            if (EnemyListBox.SelectedItem is XmlElement)
            {
                NewEnemyInstanceWindow instWindow = new NewEnemyInstanceWindow((XmlElement)EnemyListBox.SelectedItem);
                var helper = new WindowInteropHelper(instWindow);
                helper.Owner = new WindowInteropHelper(this).Handle;
                bool? res = instWindow.ShowDialog();
                if (res != null && (bool)res)
                {

                }
                else
                {
                    //MessageBox.Show("Did not add new enemy");
                }
            }
            else
            {
                MessageBox.Show("You must select one enemy before adding an instance");
            }
        }
        private void EnemyStatViewDisplay_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count > 0)
            {
                var xmlAttr = (XmlAttribute)e.AddedItems[0];
                if (StatDescriptors.ContainsKey(xmlAttr.Name))
                {
                    EnemyStatDescriptionBox.Text = StatDescriptors[xmlAttr.Name];
                }
            }
        }
        /*private void EnemyListBox_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            EnemyCountLabel.Content = EnemyListBox.Items.Count;
            if (e.Action == NotifyCollectionChangedAction.Add)
            {
                EnemyListBox.ScrollIntoView(e.NewItems[0]);
                
            }
            else if (e.Action == NotifyCollectionChangedAction.Remove)
            {
            }
            else if (e.Action == NotifyCollectionChangedAction.Reset)
            {
            }
        }*/
        private void NewEnemyFromTemplate_Click(object sender, RoutedEventArgs e)
        {
            var xmlEle = EnemyListBox.SelectedItem;
            if (xmlEle != null && xmlEle is XmlElement)
            {
                NewEnemyWindow eneWindow = new NewEnemyWindow((XmlElement)xmlEle, this);
                var helper = new WindowInteropHelper(eneWindow);
                helper.Owner = new WindowInteropHelper(this).Handle;
                bool? res = eneWindow.ShowDialog();
                if (res != null && (bool)res)
                {
                }
                else
                {
                    //MessageBox.Show("Did not add new enemy");
                }
            }
            /*NewEnemyWindow eneWindow = new NewEnemyWindow(dataProv.Document);
            var helper = new WindowInteropHelper(eneWindow);
            helper.Owner = new WindowInteropHelper(this).Handle;
            bool? res = eneWindow.ShowDialog();
            if (res != null && (bool)res)
            {
            }
            else
            {
                MessageBox.Show("Did not add new enemy");
            }*/
        }

        private void AddNewEnemy_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("EnemyDB"))
            {
                XmlDataProvider dataProv = (XmlDataProvider)this.Resources["EnemyDB"];
                if (dataProv.Document != null)
                {
                    NewEnemyWindow eneWindow = new NewEnemyWindow(dataProv.Document, this);
                    var helper = new WindowInteropHelper(eneWindow);
                    helper.Owner = new WindowInteropHelper(this).Handle;
                    bool? res = eneWindow.ShowDialog();
                    if (res != null && (bool)res)
                    {
                    }
                    else
                    {
                        // MessageBox.Show("Did not add new enemy");
                    }
                }
                else
                {
                    Console.Out.WriteLine("There is no valid Enemy XML file to add enemy to!");
                }

            }
        }

        private void DeleteCurrentEnemy_Click(object sender, RoutedEventArgs e)
        {
            var item = EnemyListBox.SelectedItem;
            if (item != null && item is XmlElement)
            {
                var xmlItem = (XmlElement)item;
                if (MessageBox.Show("Are you sure you want to delete " + xmlItem.GetAttribute("name") + "?", "Confirm Deleteion", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    xmlItem.ParentNode.RemoveChild(xmlItem);
                    EnemyNameLabel.Content = "";
                }

            }
        }
        #endregion

        

        #region Item Tab Region
        
        #endregion

        private void button1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SaveAllButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                XmlDataProvider xmlDP = (XmlDataProvider)this.FindResource("EnemiesXML");
                xmlDP.Document.Save(xmlDP.Source.LocalPath);
            }
            catch (System.Exception ex)
            {
                Console.Out.WriteLine("Could not write XML File " + ex.Message);
            }
            //EnemiesXML.Document.Save(EnemiesXML.Source.LocalPath));
        }

        private void SaveAllEnemiesButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("EnemyDB"))
            {
                XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["EnemyDB"];
                xmlDP.Document.Save(EnemyDBFile.Text);

            }
        }
        #region Game Files Tab
        private void BrowseForEnemyXML_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.CheckFileExists = true;
            dlg.DefaultExt = ".xml";
            dlg.Filter = "XML Documents (.xml)|*.xml";
            bool? res = dlg.ShowDialog();
            if (res == true)
            {
                EnemyDBFile.Text = dlg.FileName;
                if (this.Resources.Contains("EnemyDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["EnemyDB"];
                    xmlDP.Source = new Uri(dlg.FileName, UriKind.Absolute);

                }
            }
        }

        
        #endregion

        #region Items

        static string ItemIconDir = System.Configuration.ConfigurationManager.AppSettings["ItemImageDirectory"];
        private void ItemListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ItemComponentAttachmentGrid.Children.Clear();
            if (e.AddedItems.Count > 0)
            {
                string name = ((XmlElement)e.AddedItems[0]).GetAttribute("name");
                string path = ItemIconDir + name + ".png";
                ActiveItemNameLabel.Content = name;//.ToString();
                var pathtest = System.IO.Directory.GetCurrentDirectory();
                if (System.IO.File.Exists(path))
                {
                    BitmapImage AIcon = new BitmapImage();
                    AIcon.BeginInit();
                    AIcon.UriSource = new Uri(pathtest + "\\" + path, UriKind.Absolute);
                    AIcon.EndInit();
                    ItemIcon.Source = AIcon;
                }
                if (ItemListBox.SelectedItem != null && ItemListBox.SelectedItem is XmlElement)
                {
                    XmlElement xmlEle = (XmlElement)ItemListBox.SelectedItem;
                    string xmlEleName = xmlEle.GetAttribute("name");
                    if (xmlEleName != null && !xmlEleName.Equals(string.Empty))
                    {
                        foreach (var familyMember in OtherFamilyMembers.Items)
                        {
                            if (((XmlAttribute)familyMember).Value.Equals(xmlEleName))
                            {
                                OtherFamilyMembers.SelectedItem = (XmlAttribute)familyMember;
                                break;
                            }
                        }
                    }

                }
            }
        }

        private void BrowseForItemsXML_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.CheckFileExists = true;
            dlg.DefaultExt = ".xml";
            dlg.Filter = "XML Documents (.xml)|*.xml";
            bool? res = dlg.ShowDialog();
            if (res == true)
            {
                ItemsDBFile.Text = dlg.FileName;
                if (this.Resources.Contains("ItemDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ItemDB"];
                    xmlDP.Source = new Uri(dlg.FileName, UriKind.Absolute);

                }
            }
        }

        private void ItemFamily_TextChanged(object sender, TextChangedEventArgs e)
        {
            var binder = new Binding();
            binder.XPath = "../Item[Family[@value=\'" + ItemFamily.Text + "\']]/@name";
            OtherFamilyMembers.SetBinding(ComboBox.ItemsSourceProperty, binder);
            if (ItemListBox.SelectedItem != null && ItemListBox.SelectedItem is XmlElement)
            {
                XmlElement xmlEle = (XmlElement)ItemListBox.SelectedItem;
                string xmlEleName = xmlEle.GetAttribute("name");
                if (xmlEleName != null && !xmlEleName.Equals(string.Empty))
                {
                    foreach (var familyMember in OtherFamilyMembers.Items)
                    {
                        if (((XmlAttribute)familyMember).Value.Equals(xmlEleName))
                        {
                            OtherFamilyMembers.SelectedItem = (XmlAttribute)familyMember;
                            break;
                        }
                    }
                }
                
            }
        }

        private void ItemListBox_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            ItemCountLabel.Content = ItemListBox.Items.Count;
            if (e.Action == NotifyCollectionChangedAction.Add)
            {


                ItemListBox.ScrollIntoView(e.NewItems[0]);
            }
            /*else if (e.Action == NotifyCollectionChangedAction.Remove)
            {
                EnemyCountLabel.Content = EnemyListBox.Items.Count;
            }*/
        }

        private void ItemListBox_SourceUpdated(object sender, DataTransferEventArgs e)
        {

        }

        private void OtherFamilyMembers_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ItemListBox.Items.Count > 0 && OtherFamilyMembers.SelectedItem != null && OtherFamilyMembers.SelectedItem is XmlAttribute)
            {
                string newItemName = (((XmlAttribute)OtherFamilyMembers.SelectedItem).Value);
                if (newItemName != null && !newItemName.Equals(string.Empty))
                {
                    foreach (var item in ItemListBox.Items)
                    {
                        var xmlitem = item as XmlElement;
                        if (xmlitem != null)
                        {
                            if (xmlitem.GetAttribute("name").Equals(newItemName))
                            {
                                ItemListBox.SelectedItem = xmlitem;
                                break;
                            }
                        }
                        
                    }
                }
                
                // = OtherFamilyMembers.SelectedItem;
            }
        }

        private void SaveAllItemChanges_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("ItemDB"))
            {
                XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ItemDB"];
                xmlDP.Document.Save(ItemsDBFile.Text);

            }
        }

        private void AddnewItemClassButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("ItemDB"))
            {
                XmlDataProvider dataProv = (XmlDataProvider)this.Resources["ItemDB"];
                if (dataProv.Document != null)
                {
                    try
                    {
                       
                        var allItemClasses = dataProv.Document.DocumentElement.GetElementsByTagName("AllClasses");
                        if (allItemClasses.Count < 1)
                        {
                            dataProv.Document.DocumentElement.PrependChild(dataProv.Document.CreateElement("AllClasses"));
                            allItemClasses = dataProv.Document.DocumentElement.GetElementsByTagName("AllClasses");
                        }
                        ItemWindows.AddNewItemClass itemWin = new WPFTools.ItemWindows.AddNewItemClass((XmlElement)allItemClasses[0]);
                        var helper = new WindowInteropHelper(itemWin);
                        helper.Owner = new WindowInteropHelper(this).Handle;
                        bool? res = itemWin.ShowDialog();
                    }
                    catch(Exception ex)
                    {
                        Console.Out.WriteLine("Exception occured while fetch root item classes. Exception: " + ex.Message);
                    }
                }
            }
            //ItemWindows.AddNewItemClass itemWin = new WPFTools.ItemWindows.AddNewItemClass(
            /*
             * NewEnemyWindow eneWindow = new NewEnemyWindow(dataProv.Document, this);
                    var helper = new WindowInteropHelper(eneWindow);
                    helper.Owner = new WindowInteropHelper(this).Handle;
                    bool? res = eneWindow.ShowDialog();
                    if (res != null && (bool)res)
                    {
                    }
                    else
                    {
                        //MessageBox.Show("Did not add new enemy");
                    }
             */
        }
        static string xsltPath = @"";
        private void SortItemsSelect_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var sortType = SortItemsSelect.SelectedItem as ComboBoxItem;
            if (sortType != null && !sortType.Content.Equals(string.Empty))
            {
                if (this.Resources.Contains("ItemDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ItemDB"];
                    string xsltPath = System.Configuration.ConfigurationManager.AppSettings["XSLTDirectory"];
                    //xmlDP.Document.Save(xmlDP.Source.AbsolutePath);
                    //xmlDP.Document.
                    
                    switch (sortType.Content.ToString().ToLower())
                    {
                        case "alphabetical":
                            {
                                string path = xsltPath + "SortItemName.xslt";
                                if (System.IO.File.Exists(path))
                                {
                                    var source = xmlDP.Source;
                                    XslCompiledTransform compTrans = new XslCompiledTransform();
                                    compTrans.Load(path);
                                    XmlDocument res = new XmlDocument();
                                    using (XmlWriter writer = res.CreateNavigator().AppendChild())
                                    {
                                        compTrans.Transform(xmlDP.Document, null, writer);
                                        writer.Close();
                                    }
                                    xmlDP.Document = res;
                                    //xmlDP.Source = source;
                                   /* XslCompiledTransform compTrans = new XslCompiledTransform();
                                    compTrans.Load(path);
                                    XmlWriter writer = XmlWriter.Create()
                                    compTrans.Transform(xmlDP.Document, new XsltArgumentList(), xmlDP.Document.XmlResolver);
                                    XslTransform trans = new XslTransform();
                                    trans.Load(path);
                                    var ret = trans.Transform(xmlDP.Document, null, null);*/
                                    //trans.Transform(xmlDP.Document, );
                                }
                                else
                                {
                                    Console.Out.WriteLine("Failed to load xslt from " + path);
                                }
                            }
                            break;
                        case "families":
                            {
                                string path = xsltPath + "SortItemFamily.xslt";
                                if (System.IO.File.Exists(path))
                                {
                                    var source = xmlDP.Source;
                                    XslCompiledTransform compTrans = new XslCompiledTransform();
                                    compTrans.Load(path);
                                    XmlDocument res = new XmlDocument();
                                    using (XmlWriter writer = res.CreateNavigator().AppendChild())
                                    {
                                        compTrans.Transform(xmlDP.Document, null, writer);
                                        writer.Close();
                                    }
                                    xmlDP.Document = res;
                                }
                                else
                                {
                                    Console.Out.WriteLine("Failed to load xslt from " + path);
                                }
                            }
                            break;
                        case "value":
                            {
                                string path = xsltPath + "SortItemValue.xslt";
                                if (System.IO.File.Exists(path))
                                {
                                    var source = xmlDP.Source;
                                    XslCompiledTransform compTrans = new XslCompiledTransform();
                                    compTrans.Load(path);
                                    XmlDocument res = new XmlDocument();
                                    using (XmlWriter writer = res.CreateNavigator().AppendChild())
                                    {
                                        compTrans.Transform(xmlDP.Document, null, writer);
                                        writer.Close();
                                    }
                                    xmlDP.Document = res;
                                }
                                else
                                {
                                    Console.Out.WriteLine("Failed to load xslt from " + path);
                                }
                            }
                            break;
                        case "types":
                            {
                                string path = xsltPath + "SortItemType.xslt";
                                if (System.IO.File.Exists(path))
                                {
                                    var source = xmlDP.Source;
                                    XslCompiledTransform compTrans = new XslCompiledTransform();
                                    compTrans.Load(path);
                                    XmlDocument res = new XmlDocument();
                                    using (XmlWriter writer = res.CreateNavigator().AppendChild())
                                    {
                                        compTrans.Transform(xmlDP.Document, null, writer);
                                        writer.Close();
                                    }
                                    xmlDP.Document = res;
                                }
                                else
                                {
                                    Console.Out.WriteLine("Failed to load xslt from " + path);
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        private void DelItemComponent_Click(object sender, RoutedEventArgs e)
        {
            if (ItemComponentList.SelectedItem != null)
            {
                XmlElement component = ItemComponentList.SelectedItem as XmlElement;
                if (component != null)
                {
                    ItemComponentAttachmentGrid.Children.Clear();
                    component.ParentNode.RemoveChild(component);
                }
            }
        }

        private void AddAvailableClass_Click(object sender, RoutedEventArgs e)
        {
            if (AvailableItemClasses.SelectedItem != null)
            {
                XmlAttribute newClass = AvailableItemClasses.SelectedItem as XmlAttribute;
                if (newClass != null)
                {
                    var itemClassElement = AvailableItemClasses.DataContext as XmlElement;
                    if (itemClassElement != null)
                    {
                        var itemClasses = itemClassElement.SelectNodes("Classes");
                        if (itemClasses.Count > 0)
                        {
                            //check if class already exists
                            var check = itemClasses[0].SelectNodes("Class[@value=\'" + newClass.Value + "\']");
                            if (check.Count == 0)
                            {
                                itemClasses[0].AppendChild(newClass.OwnerElement.Clone());
                            }
                        }
                    }

                }
            }
        }

        private void RemoveCurrentClass_Click(object sender, RoutedEventArgs e)
        {
            if (ItemCurrentClasses.SelectedItem != null)
            {
                XmlAttribute itemClass = ItemCurrentClasses.SelectedItem as XmlAttribute;
                if (itemClass != null)
                {
                    itemClass.OwnerElement.ParentNode.RemoveChild(itemClass.OwnerElement);
                }
            }
        }

        private void MoveItemClassUp_Click(object sender, RoutedEventArgs e)
        {
            if (ItemCurrentClasses.Items.Count > 1)
            {
                var moveNode = ItemCurrentClasses.SelectedItem as XmlAttribute;
                if (moveNode != null)
                {
                    if (moveNode.OwnerElement.PreviousSibling != null)
                    {
                        moveNode.OwnerElement.ParentNode.InsertBefore(moveNode.OwnerElement, moveNode.OwnerElement.PreviousSibling);
                    }
                }
            }
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            if (ItemCurrentClasses.Items.Count > 1)
            {
                var moveNode = ItemCurrentClasses.SelectedItem as XmlAttribute;
                if (moveNode != null)
                {
                    if (moveNode.OwnerElement.NextSibling != null)
                    {
                        moveNode.OwnerElement.ParentNode.InsertAfter(moveNode.OwnerElement, moveNode.OwnerElement.NextSibling);
                    }
                }
            }
        }

        #endregion

        #region Actions

        private void ActionListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //ItemComponentAttachmentGrid.Children.Clear();
            if (e.AddedItems.Count > 0)
            {
                string name = ((XmlElement)e.AddedItems[0]).GetAttribute("name");
                //string path = ItemIconDir + name + ".png";
                ActiveActionNameLabel.Content = name;

                if (ActionListBox.SelectedItem != null && ActionListBox.SelectedItem is XmlElement)
                {
                    XmlElement xmlEle = (XmlElement)ActionListBox.SelectedItem;
                    bool cont = true;
                    //while (cont)
                    {
                        XmlNodeList flags = xmlEle.SelectNodes("Flags/*");
                        int count = flags.Count;
                    }
                    
                }






                if (ItemListBox.SelectedItem != null && ItemListBox.SelectedItem is XmlElement)
                {
                    XmlElement xmlEle = (XmlElement)ItemListBox.SelectedItem;
                    string xmlEleName = xmlEle.GetAttribute("name");
                    if (xmlEleName != null && !xmlEleName.Equals(string.Empty))
                    {
                        foreach (var familyMember in OtherFamilyMembers.Items)
                        {
                            if (((XmlAttribute)familyMember).Value.Equals(xmlEleName))
                            {
                                OtherFamilyMembers.SelectedItem = (XmlAttribute)familyMember;
                                break;
                            }
                        }
                    }

                }
            }
        }

        private void BrowseForActionsXML_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.CheckFileExists = true;
            dlg.DefaultExt = ".xml";
            dlg.Filter = "XML Documents (.xml)|*.xml";
            bool? res = dlg.ShowDialog();
            if (res == true)
            {
                ActionDBFile.Text = dlg.FileName;
                if (this.Resources.Contains("ActionDB"))
                {
                    XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ActionDB"];
                    xmlDP.Source = new Uri(dlg.FileName, UriKind.Absolute);

                }
            }
        }

        private void ActionListBox_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            ActionCount.Content = ActionListBox.Items.Count;
            if (e.Action == NotifyCollectionChangedAction.Add)
            {
                ActionListBox.ScrollIntoView(e.NewItems[0]);
            }
            /*else if (e.Action == NotifyCollectionChangedAction.Remove)
            {
                EnemyCountLabel.Content = EnemyListBox.Items.Count;
            }*/
        }

        #endregion

        void Test()
        {
            XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ItemDB"];
            string xsltPath = System.Configuration.ConfigurationManager.AppSettings["XSLDirextory"];
            string path = xsltPath + "SortItemName.xslt";
            if (System.IO.File.Exists(path))
            {
                XslCompiledTransform compTrans = new XslCompiledTransform();
                compTrans.Load(path);
                //compTrans.Transform(xmlDP.Document, new XsltArgumentList(), xmlDP.Document.XmlResolver);
            }

        }

        private void ComponentList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count > 0)
            {
                XmlElement ele = e.AddedItems[0] as XmlElement;
                switch (ele.Name.ToLower())
                {
                    case "healingcomponents":
                        {
                            ItemComponentAttachmentGrid.Children.Clear();
                            ItemComponentAttachmentGrid.Children.Add(new ComponentControls.ItemComponents.HealingComponent(ele, (XmlElement)ItemListBox.SelectedItem));
                        }
                        break;
                    case "synthesisrecipecomponent":
                        {
                            ItemComponentAttachmentGrid.Children.Clear();
                            ItemComponentAttachmentGrid.Children.Add(new ComponentControls.ItemComponents.SynthesisRecipeComponent(ele, (XmlElement)ItemListBox.SelectedItem));
                        }
                        break;
                }
            }
        }

        

        private void AddEnemySERes_Click(object sender, RoutedEventArgs e)
        {
            var instWindow = new WPFTools.Popups.AddStatusEffect((XmlElement)((XmlElement)EnemyLevelsListBox.SelectedItem).SelectSingleNode("StatusResistances"), "Resistance");
            var helper = new WindowInteropHelper(instWindow);
            helper.Owner = new WindowInteropHelper(this).Handle;
            bool? res = instWindow.ShowDialog();
            if (res != null && res == true)
            {
            }
            else
            {
            }
            /*
             *  NewEnemyInstanceWindow instWindow = new NewEnemyInstanceWindow(this.NewEnemyElement);
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
             */
        }

        private void RemoveEnemyStatusResistance_Click(object sender, RoutedEventArgs e)
        {
            XmlElement removal = EnemyStatusResistancesGrid.SelectedItem as XmlElement;
            if (removal != null)
            {
                removal.ParentNode.RemoveChild(removal);
            }
        }

        #region Mapper
        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32")]
        private static extern IntPtr SetParent(IntPtr hWnd, IntPtr hWndParent);

        [DllImport("user32")]
        private static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, int uFlags);

        private const int SWP_NOZORDER = 0x0004;
        private const int SWP_NOACTIVATE = 0x0010;
        private const int GWL_STYLE = -16;
        private const int WS_CAPTION = 0x00C00000;
        private const int WS_THICKFRAME = 0x00040000; 

        protected void InitializeTiled()
        {

        }

        #endregion

        private void AddEnemyEleEff_Click(object sender, RoutedEventArgs e)
        {

        }

        private void RemoveEnemyEleEff_Click(object sender, RoutedEventArgs e)
        {
            XmlElement removal = EnemyElementalEffectivenessGrid.SelectedItem as XmlElement;
            if (removal != null)
            {
                removal.ParentNode.RemoveChild(removal);
            }
        }

        private void OutputEnumCode_Click(object sender, RoutedEventArgs e)
        {
            string myText = new TextRange(EnumInBox.Document.ContentStart, EnumInBox.Document.ContentEnd).Text;
            if (myText.Length > 0)
            {
                try
                {
                    EnumOutBox.Document.Blocks.Clear();
                    string[] lines = myText.Split(new string[] { "\n" }, StringSplitOptions.RemoveEmptyEntries);
                    int lastSpaceIndex = lines[0].LastIndexOf(" ");
                    string enumName = lines[0].Substring(lastSpaceIndex, lines[0].Length - lastSpaceIndex).Trim();
                    StringBuilder output1 = new StringBuilder();
                    StringBuilder output2 = new StringBuilder();
                    output1.AppendLine("boost::unordered_map<std::string, " + enumName + "> = boost::assign::map_list_of");
                    output2.AppendLine("boost::unordered_map<" + enumName + ", std::string> = boost::assign::map_list_of");
                    for (int i = 1; i < lines.Length; ++i)
                    {
                        
                        lines[i] = lines[i].Trim();
                        lines[i] = lines[i].Replace("\r", String.Empty);
                        lines[i] = lines[i].Replace("\t", String.Empty);
                        lines[i] = lines[i].Replace("\n", String.Empty);
                        lines[i] = lines[i].Replace(",", String.Empty);
                        if (lines[i] != "};" && lines[i] != "{" && lines[i] != String.Empty)
                        {
                            int commentIndex = lines[i].IndexOf("//");
                            if (commentIndex > 0)
                            {
                                lines[i] = lines[i].Substring(0, commentIndex).Trim();
                            }
                            output1.AppendLine("\t(\"" + lines[i] + "\", " + enumName + "::" + lines[i] + ")");
                            output2.AppendLine("\t(" + enumName + "::" + lines[i] + ", \"" + lines[i] + "\")");
                        }
                        
                    }
                    output1.AppendLine(";");
                    output2.AppendLine(";");
                    output1.Append(output2.ToString());
                    EnumOutTextBox.Text = output1.ToString();
                    //System.IO.MemoryStream stream = new System.IO.MemoryStream(ASCIIEncoding.Default.GetBytes(output1.ToString()));
                    //this.EnumOutBox.Selection.Load(stream, DataFormats.Rtf);
                }
                catch (System.Exception ex)
                {
                   
                }
                
            }
        }

        #region Graphic Tools Tab
        SFML.Graphics.Shader TestShader = null;
        SFML.Graphics.Sprite ShaderSprite = null;
        Stopwatch ShaderTimer = null;
        Controls.SFMLRenderControl ShaderControl = null;
        string timeParam = "time";
        string selfTexture = "texture";
        string resParam = "resolution";
        private void InitiateShaderData()
        {
            if (SFML.Graphics.Shader.IsAvailable)
            {
              
                ShaderControl = new Controls.SFMLRenderControl(30u, (int)SFMLShaderHost.Width, (int)SFMLShaderHost.Height);
                SFMLShaderHost.Child = ShaderControl;
                ShaderControl.Drawing += HandleDrawing;
                ShaderTimer = new Stopwatch();
                //SFMLShaderHost.
                //SFMLShaderHost.
            }
        }
        private void HandleDrawing(Controls.SFMLRenderControl control)
        {
            if (control.GlobalShader != null && ShaderTimer != null)
                control.GlobalShader.SetParameter(timeParam, (float)ShaderTimer.ElapsedMilliseconds * 0.001f);
            //ShaderEditorBox.InvalidateVisual();
        }
        private void ActivateShader_MouseEnter(object sender, MouseEventArgs e)
        {
        }
        private void ActivateShader_Click(object sender, RoutedEventArgs e)
        {
            ShaderErrorBox.Document.Blocks.Clear();
            if (SFML.Graphics.Shader.IsAvailable)
            {
                string shaderText = new TextRange(ShaderEditorBox.Document.ContentStart, ShaderEditorBox.Document.ContentEnd).Text;
                if (shaderText.Length < 1)
                {
                    ShaderErrorBox.AppendText("Error: There is no shader data.");
                }
                else
                {
                    if (TestShader != null)
                    {
                        TestShader.Dispose();
                        
                    }
                    try
                    {
                        lock (ShaderControl.DrawLocked)
                        {
                            TestShader = SFML.Graphics.Shader.FromString(shaderText);
                            TestShader.SetCurrentTexture(selfTexture);
                            if (UseImageRes.IsChecked == true && ShaderSprite != null)
                            {
                                TestShader.SetParameter(resParam, 1.0f, 1.0f);
                            }
                            else
                            {
                                TestShader.SetParameter(resParam, (float)ShaderControl.Width, (float)ShaderControl.Height);
                            }
                            if (ShaderControl != null)
                            {
                                ShaderControl.GlobalShader = TestShader;
                            }
                            ShaderTimer.Reset();
                            ShaderTimer.Start();
                            TestShader.SetParameter(timeParam, (float)ShaderTimer.ElapsedMilliseconds);
                        }

                    }
                    catch (SFML.LoadingFailedException ex)
                    {
                        ShaderErrorBox.AppendText("Error: " + ex.Message);
                    }
                    catch (Exception ex)
                    {
                        ShaderErrorBox.AppendText("Error: " + ex.Message);
                    }
                }
            }
            else
            {
                ShaderErrorBox.AppendText("Error: Your system does not support shaders.");
            }
        }

        private void LoadImageForShader_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.CheckFileExists = true;
            dlg.DefaultExt = ".png";
            dlg.Filter = "Images (.png, .jpg, .gif)|*.png;*.jpg;*.gif";
            bool? res = dlg.ShowDialog();
            if (res == true)
            {
                BitmapImage shaderImage = new BitmapImage();
                
                shaderImage.BeginInit();
                shaderImage.UriSource = new Uri(dlg.FileName, UriKind.Absolute);
                shaderImage.EndInit();
                PreShaderImage.Source = shaderImage;
                lock (ShaderControl.DrawLocked)
                {
                    if (ShaderSprite != null)
                        ShaderSprite.Dispose();

                    ShaderSprite = new SFML.Graphics.Sprite(new SFML.Graphics.Texture(dlg.FileName));
                    if (ShaderControl != null)
                    {
                        ShaderControl.DrawableSprites.Clear();
                        ShaderControl.DrawableSprites.Add(ShaderSprite);
                    }
                }
                
                /*
                 * BitmapImage AIcon = new BitmapImage();
                    AIcon.BeginInit();
                    AIcon.UriSource = new Uri(pathtest + "\\" + path, UriKind.Absolute);
                    AIcon.EndInit();
                    ItemIcon.Source = AIcon;
                 */
            }
        }
        #endregion

        private void SaveToPreDefSource_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ResetShader_Click(object sender, RoutedEventArgs e)
        {
            InitiateShaderData();
        }

        private void AddNewItemButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("ItemDB"))
            {
                XmlDataProvider dataProv = (XmlDataProvider)this.Resources["ItemDB"];
                if (dataProv.Document != null)
                {
                    var itemRoot = dataProv.Document.ChildNodes.Item(0) as XmlElement;

                    ItemWindows.AddNewItem itWin = new ItemWindows.AddNewItem(itemRoot, this);
                    var helper = new WindowInteropHelper(itWin);
                    helper.Owner = new WindowInteropHelper(this).Handle;
                    bool? res = itWin.ShowDialog();
                    if (res != null && (bool)res)
                    {
                    }
                    else
                    {
                        //MessageBox.Show("Did not add new enemy");
                    }
                }
            }
            else
            {
                Console.Out.WriteLine("There is no valid Item XML file to add item to");
            }
        }

        private void SaveAllActions_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("ActionDB"))
            {
                XmlDataProvider xmlDP = (XmlDataProvider)this.Resources["ActionDB"];
                xmlDP.Document.Save(ActionDBFile.Text);

            }
        }

        private void ActionComponentList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count > 0)
            {
                ActionComponentGrid.Children.Clear();
                XmlElement ele = e.AddedItems[0] as XmlElement;
                switch (ele.Name.ToLower())
                {
                    case "elementalweightcomponent":
                        {
                            ActionComponentGrid.Children.Add(new ComponentControls.ActionComponents.ElementalWeightComponent((XmlElement)ActionComponentList.SelectedItem, ele));
                        }
                        break;
                    case "synthesisrecipecomponent":
                        {
                            ItemComponentAttachmentGrid.Children.Add(new ComponentControls.ItemComponents.SynthesisRecipeComponent(ele, (XmlElement)ItemListBox.SelectedItem));
                        }
                        break;
                    default:
                        break;
                }
            }
        }





        /*
         * private void AddNewEnemyButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.Resources.Contains("EnemyDB"))
            {
                XmlDataProvider dataProv = (XmlDataProvider)this.Resources["EnemyDB"];
                if (dataProv.Document != null)
                {
                    NewEnemyWindow eneWindow = new NewEnemyWindow(dataProv.Document, this);
                    var helper = new WindowInteropHelper(eneWindow);
                    helper.Owner = new WindowInteropHelper(this).Handle;
                    bool? res = eneWindow.ShowDialog();
                    if (res != null && (bool)res)
                    {
                    }
                    else
                    {
                        //MessageBox.Show("Did not add new enemy");
                    }
                }
                else
                {
                    Console.Out.WriteLine("There is no valid Enemy XML file to add enemy to!");
                }
                
            }
            
        }
         * */


    }
}
