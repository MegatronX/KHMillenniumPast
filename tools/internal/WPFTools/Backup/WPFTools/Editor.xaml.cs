using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data;
namespace WPFTools
{
    /// <summary>
    /// Interaction logic for Editor.xaml
    /// </summary>
    public partial class Editor : Window
    {
        DataSet Stats = new DataSet();
        public Editor()
        {
            InitializeComponent();
            
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

        #endregion

        

        #region Item Tab Region
        private void ItemListBox_SourceUpdated(object sender, DataTransferEventArgs e)
        {
            ItemCountLabel.Content = ItemListBox.Items.Count;
        }

        private void ItemListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count > 0)
            {
                ActiveItemNameLabel.Content = e.AddedItems[0].ToString();
            }
        }
        #endregion
    }
}
