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
    /// Interaction logic for HealingComponent.xaml
    /// </summary>
    public partial class HealingComponent : UserControl
    {
        bool DoingInitialLoad = false;
        XmlElement rootComponentElement;
        XmlElement itemElement;
        public XmlElement RootComponentElement
        {
            get { return rootComponentElement; }
            set { rootComponentElement = value; }
        }
        public XmlElement ItemElement
        {
            get { return itemElement; }
            set { itemElement = value; }
        }
        public HealingComponent(XmlElement element, XmlElement itemElement)
        {
            DoingInitialLoad = true;
            rootComponentElement = element;
            this.itemElement = itemElement;
            InitializeComponent();
            CheckComponentsSet();
            DoingInitialLoad = false;
        }
        void CheckComponentsSet()
        {
            #region Battle Use
            XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
            XmlElement ele;
            if (BattleHealingElements.Count > 0)
            {
                ele = (XmlElement)BattleHealingElements[0];
                XmlNodeList BattleHealing = ele.SelectNodes("HP");
                if (BattleHealing.Count > 0)
                {
                    //XmlElement hpele = (XmlElement)BattleHealing[0];
                    UseBattleHPHealing.IsChecked = true;
                }
                BattleHealing = ele.SelectNodes("MP");
                if (BattleHealing.Count > 0)
                {
                    //XmlElement hpele = (XmlElement)BattleHealing[0];
                    UseBattleMPHealing.IsChecked = true;
                }
                BattleHealing = ele.SelectNodes("SP");
                if (BattleHealing.Count > 0)
                {
                    //XmlElement hpele = (XmlElement)BattleHealing[0];
                    UseBattleSPHealing.IsChecked = true;
                }
            }
            else
            {
               // ele = rootComponentElement.OwnerDocument.CreateElement("BattleHealingComponent");
               // rootComponentElement.AppendChild(rootComponentElement.AppendChild(ele));
            }
            #endregion
            #region field user
            XmlNodeList FieldHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
            if (FieldHealingElements.Count > 0)
            {
                ele = (XmlElement)FieldHealingElements[0];
                XmlNodeList BattleHealing = ele.SelectNodes("HP");
                if (BattleHealing.Count > 0)
                {
                    //XmlElement hpele = (XmlElement)BattleHealing[0];
                    UseFieldHPHealing.IsChecked = true;
                }
                BattleHealing = ele.SelectNodes("MP");
                if (BattleHealing.Count > 0)
                {
                    //XmlElement hpele = (XmlElement)BattleHealing[0];
                    UseFieldMPHealing.IsChecked = true;
                }
                BattleHealing = ele.SelectNodes("SP");
                if (BattleHealing.Count > 0)
                {
                    //XmlElement hpele = (XmlElement)BattleHealing[0];
                    UseFieldSPHealing.IsChecked = true;
                }
            }
            #endregion
        }
        private void UseFieldHPHealing_Checked(object sender, RoutedEventArgs e)
        {
            if (!DoingInitialLoad)
            {
                if (UseFieldHPHealing.IsChecked == true)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];
                    }
                    else
                    {
                        ele = rootComponentElement.OwnerDocument.CreateElement("FieldHealingComponent");
                        rootComponentElement.AppendChild(ele);//rootComponentElement.AppendChild(ele));
                    }
                    XmlNodeList HPHealingElements = ele.SelectNodes("HP");
                    if (HPHealingElements.Count == 0)
                    {
                        XmlElement hphealer = ele.OwnerDocument.CreateElement("HP");
                        ele.AppendChild(hphealer);
                        hphealer.SetAttribute("amount", "0");
                        hphealer.SetAttribute("type", "Absolute");

                    }
                }
                else if (UseFieldHPHealing.IsChecked == false)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];

                        XmlNodeList HPHealingElements = ele.SelectNodes("HP");
                        if (HPHealingElements.Count > 0)
                        {
                            foreach (XmlNode element in HPHealingElements)
                            {
                                element.ParentNode.RemoveChild(element);
                            }
                        }
                    }
                }
            }
        }

        private void UseBattleHPHealing_Checked(object sender, RoutedEventArgs e)
        {
            if (!DoingInitialLoad)
            {
                if (UseBattleHPHealing.IsChecked == true)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];
                    }
                    else
                    {
                        ele = rootComponentElement.OwnerDocument.CreateElement("BattleHealingComponent");
                        rootComponentElement.AppendChild(ele);//rootComponentElement.AppendChild(ele));
                    }
                    XmlNodeList HPHealingElements = ele.SelectNodes("HP");
                    if (HPHealingElements.Count == 0)
                    {
                        XmlElement hphealer = ele.OwnerDocument.CreateElement("HP");
                        ele.AppendChild(hphealer);
                        hphealer.SetAttribute("amount", "0");
                        hphealer.SetAttribute("type", "Absolute");
                        
                    }
                }
                else if (UseBattleHPHealing.IsChecked == false)
                {
                     XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];

                        XmlNodeList HPHealingElements = ele.SelectNodes("HP");
                        if (HPHealingElements.Count > 0)
                        {
                            foreach (XmlNode element in HPHealingElements)
                            {
                                element.ParentNode.RemoveChild(element);
                            }
                        }
                    }
                }
            }
            
        }

        private void UseBattleMPHealing_Checked(object sender, RoutedEventArgs e)
        {
            if (!DoingInitialLoad)
            {
                if (UseBattleMPHealing.IsChecked == true)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];
                    }
                    else
                    {
                        ele = rootComponentElement.OwnerDocument.CreateElement("BattleHealingComponent");
                        rootComponentElement.AppendChild(ele);//rootComponentElement.AppendChild(ele));
                    }
                    XmlNodeList HPHealingElements = ele.SelectNodes("MP");
                    if (HPHealingElements.Count == 0)
                    {
                        XmlElement hphealer = ele.OwnerDocument.CreateElement("MP");
                        ele.AppendChild(hphealer);
                        hphealer.SetAttribute("amount", "0");
                        hphealer.SetAttribute("type", "Absolute");

                    }
                }
                else if (UseBattleMPHealing.IsChecked == false)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];

                        XmlNodeList MPHealingElements = ele.SelectNodes("MP");
                        if (MPHealingElements.Count > 0)
                        {
                            foreach (XmlNode element in MPHealingElements)
                            {
                                element.ParentNode.RemoveChild(element);
                            }
                        }
                    }
                }
            }
        }

        private void UseBattleSPHealing_Checked(object sender, RoutedEventArgs e)
        {
            if (!DoingInitialLoad)
            {
                if (UseBattleSPHealing.IsChecked == true)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];
                    }
                    else
                    {
                        ele = rootComponentElement.OwnerDocument.CreateElement("BattleHealingComponent");
                        rootComponentElement.AppendChild(ele);//rootComponentElement.AppendChild(ele));
                    }
                    XmlNodeList HPHealingElements = ele.SelectNodes("SP");
                    if (HPHealingElements.Count == 0)
                    {
                        XmlElement hphealer = ele.OwnerDocument.CreateElement("SP");
                        ele.AppendChild(hphealer);
                        hphealer.SetAttribute("amount", "0");
                        hphealer.SetAttribute("type", "Absolute");

                    }
                }
                else if (UseBattleSPHealing.IsChecked == false)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("BattleHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];

                        XmlNodeList SPHealingElements = ele.SelectNodes("SP");
                        if (SPHealingElements.Count > 0)
                        {
                            foreach (XmlNode element in SPHealingElements)
                            {
                                element.ParentNode.RemoveChild(element);
                            }
                        }
                    }
                }
            }
        }

        private void UseFieldMPHealing_Checked(object sender, RoutedEventArgs e)
        {
            if (!DoingInitialLoad)
            {
                if (UseFieldMPHealing.IsChecked == true)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];
                    }
                    else
                    {
                        ele = rootComponentElement.OwnerDocument.CreateElement("FieldHealingComponent");
                        rootComponentElement.AppendChild(ele);//rootComponentElement.AppendChild(ele));
                    }
                    XmlNodeList HPHealingElements = ele.SelectNodes("MP");
                    if (HPHealingElements.Count == 0)
                    {
                        XmlElement hphealer = ele.OwnerDocument.CreateElement("MP");
                        ele.AppendChild(hphealer);
                        hphealer.SetAttribute("amount", "0");
                        hphealer.SetAttribute("type", "Absolute");

                    }
                }
                else if (UseFieldMPHealing.IsChecked == false)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];

                        XmlNodeList MPHealingElements = ele.SelectNodes("MP");
                        if (MPHealingElements.Count > 0)
                        {
                            foreach (XmlNode element in MPHealingElements)
                            {
                                element.ParentNode.RemoveChild(element);
                            }
                        }
                    }
                }
            }
        }

        private void UseFieldSPHealing_Checked(object sender, RoutedEventArgs e)
        {
            if (!DoingInitialLoad)
            {
                if (UseFieldSPHealing.IsChecked == true)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];
                    }
                    else
                    {
                        ele = rootComponentElement.OwnerDocument.CreateElement("FieldHealingComponent");
                        rootComponentElement.AppendChild(ele);//rootComponentElement.AppendChild(ele));
                    }
                    XmlNodeList HPHealingElements = ele.SelectNodes("SP");
                    if (HPHealingElements.Count == 0)
                    {
                        XmlElement hphealer = ele.OwnerDocument.CreateElement("SP");
                        ele.AppendChild(hphealer);
                        hphealer.SetAttribute("amount", "0");
                        hphealer.SetAttribute("type", "Absolute");

                    }
                }
                else if (UseFieldSPHealing.IsChecked == false)
                {
                    XmlNodeList BattleHealingElements = rootComponentElement.SelectNodes("FieldHealingComponent");
                    XmlElement ele;
                    if (BattleHealingElements.Count > 0)
                    {
                        ele = (XmlElement)BattleHealingElements[0];

                        XmlNodeList SPHealingElements = ele.SelectNodes("SP");
                        if (SPHealingElements.Count > 0)
                        {
                            foreach (XmlNode element in SPHealingElements)
                            {
                                element.ParentNode.RemoveChild(element);
                            }
                        }
                    }
                }
            }
        }
    }
}
