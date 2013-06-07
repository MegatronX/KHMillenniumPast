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

namespace WPFTools.ComponentControls.ItemComponents
{
    /// <summary>
    /// Interaction logic for SynthesisRecipeComponent.xaml
    /// </summary>
    ///
    public partial class SynthesisRecipeComponent : UserControl
    {
        bool DoingInitialLoad = false;
        XmlElement rootComp;
        XmlElement itemRoot;
        public XmlElement RootComponentElement
        {
            get
            {
                return rootComp;
            }
            set
            {
                rootComp = value;
            }
        }
        public XmlElement ItemElement
        {
            get { return itemRoot; }
            set { itemRoot = value; }
        }
        public SynthesisRecipeComponent(XmlElement element, XmlElement itemElement)
        {
            DoingInitialLoad = true;
            RootComponentElement = element;
            ItemElement = itemElement;
            InitializeComponent();
            DoingInitialLoad = false;
        }
    }
}
