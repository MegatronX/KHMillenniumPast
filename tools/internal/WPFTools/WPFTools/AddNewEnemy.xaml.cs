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

namespace WPFTools
{
    /// <summary>
    /// Interaction logic for AddNewEnemy.xaml
    /// </summary>
    public partial class AddNewEnemy : UserControl
    {
        #region Events
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            
            RaiseEvent(new RoutedEventArgs(CancelButtonClickEvent));
        }
        #endregion

        #region Route Events

        public static readonly RoutedEvent CancelButtonClickEvent = EventManager.RegisterRoutedEvent(  
         "CancelButtonClick", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(AddNewEnemy));

        public event RoutedEventHandler CancelButtonClick
        {
            add { AddHandler(CancelButtonClickEvent, value); }
            remove { RemoveHandler(CancelButtonClickEvent, value); }
        }  

        #endregion
        public AddNewEnemy()
        {
            InitializeComponent();
            ParentWindow = (Window)Application.Current.MainWindow;
        }

        public void Show()
        {
            this.Visibility = Visibility.Visible;
        }

        public void Hide()
        {
            this.Visibility = Visibility.Collapsed;
        }

        private Window ParentWindow;

        
    }
}
