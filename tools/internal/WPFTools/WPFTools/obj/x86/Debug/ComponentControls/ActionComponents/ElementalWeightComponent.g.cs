﻿#pragma checksum "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "76EF03A3984896005093D95191C85743"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.269
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms.Integration;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace WPFTools.ComponentControls.ActionComponents {
    
    
    /// <summary>
    /// ElementalWeightComponent
    /// </summary>
    public partial class ElementalWeightComponent : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 8 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal WPFTools.ComponentControls.ActionComponents.ElementalWeightComponent ElementWeightUserControl;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.Label label11;
        
        #line default
        #line hidden
        
        
        #line 15 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.Button NormalizeElementWeights;
        
        #line default
        #line hidden
        
        
        #line 16 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.Button ClearElementWeights;
        
        #line default
        #line hidden
        
        
        #line 17 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.ListView ElementWeightDisplay;
        
        #line default
        #line hidden
        
        
        #line 41 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.Label label1;
        
        #line default
        #line hidden
        
        
        #line 42 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.TextBox textBox1;
        
        #line default
        #line hidden
        
        
        #line 43 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.TextBlock ElementDescription;
        
        #line default
        #line hidden
        
        
        #line 44 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
        internal System.Windows.Controls.Button AddElementWeight;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/WPFTools;component/componentcontrols/actioncomponents/elementalweightcomponent.x" +
                    "aml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.ElementWeightUserControl = ((WPFTools.ComponentControls.ActionComponents.ElementalWeightComponent)(target));
            return;
            case 2:
            this.label11 = ((System.Windows.Controls.Label)(target));
            return;
            case 3:
            this.NormalizeElementWeights = ((System.Windows.Controls.Button)(target));
            return;
            case 4:
            this.ClearElementWeights = ((System.Windows.Controls.Button)(target));
            
            #line 16 "..\..\..\..\..\ComponentControls\ActionComponents\ElementalWeightComponent.xaml"
            this.ClearElementWeights.Click += new System.Windows.RoutedEventHandler(this.ClearElementWeights_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.ElementWeightDisplay = ((System.Windows.Controls.ListView)(target));
            return;
            case 6:
            this.label1 = ((System.Windows.Controls.Label)(target));
            return;
            case 7:
            this.textBox1 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 8:
            this.ElementDescription = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 9:
            this.AddElementWeight = ((System.Windows.Controls.Button)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

