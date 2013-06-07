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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPFTools.ComponentControls.ActionComponents
{
    /// <summary>
    /// Interaction logic for ElementalWeightComponent.xaml
    /// </summary>
    public partial class ElementalWeightComponent : UserControl
    {
        bool DoingInitialLoad = false;
        public XmlElement RootAction
        {
            get;
            set;
        }

        public XmlElement ElementWeightComponent
        {
            get;
            set;
        }

        public ElementalWeightComponent(XmlElement ActionElement, XmlElement ComponentElement)
        {
            DoingInitialLoad = true;
            RootAction = ActionElement;
            ElementWeightComponent = ComponentElement;

            InitializeComponent();
            ProcessComponent();

            bool con = true;
            while (con)
            {
                var ele = ComponentElement.SelectNodes("Element");
                if (ele.Count > 0)
                {
                    int f = 0;
                    con = false;
                }
            }

            DoingInitialLoad = false;
        }

        public ElementalWeightComponent()
        {
            InitializeComponent();
        }

        private void ProcessComponent()
        {
            if (ElementWeightComponent != null)
            {

            }
        }

        private void ClearElementWeights_Click(object sender, RoutedEventArgs e)
        {
            if (ElementWeightComponent != null)
            {
                ElementWeightComponent.InnerXml = String.Empty;
            }
        }
    }
}
