﻿#pragma checksum "..\..\..\..\Popups\AddStatusEffect.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "6390E3E628440A700F5B7BD2382046EE"
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


namespace WPFTools.Popups {
    
    
    /// <summary>
    /// AddStatusEffect
    /// </summary>
    public partial class AddStatusEffect : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 4 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal WPFTools.Popups.AddStatusEffect AddStatusEffectWindow;
        
        #line default
        #line hidden
        
        
        #line 9 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.Label label3;
        
        #line default
        #line hidden
        
        
        #line 10 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.Label label1;
        
        #line default
        #line hidden
        
        
        #line 11 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.Label label2;
        
        #line default
        #line hidden
        
        
        #line 12 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.Button AddStatusEffectButton;
        
        #line default
        #line hidden
        
        
        #line 13 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.Button CancelAddStatusEffectButton;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.TextBox AddStatusEffectNameBox;
        
        #line default
        #line hidden
        
        
        #line 15 "..\..\..\..\Popups\AddStatusEffect.xaml"
        internal System.Windows.Controls.TextBox AddStatusEffectValueBox;
        
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
            System.Uri resourceLocater = new System.Uri("/WPFTools;component/popups/addstatuseffect.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\Popups\AddStatusEffect.xaml"
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
            this.AddStatusEffectWindow = ((WPFTools.Popups.AddStatusEffect)(target));
            
            #line 4 "..\..\..\..\Popups\AddStatusEffect.xaml"
            this.AddStatusEffectWindow.Closing += new System.ComponentModel.CancelEventHandler(this.AddStatusEffectWindow_Closing);
            
            #line default
            #line hidden
            return;
            case 2:
            this.label3 = ((System.Windows.Controls.Label)(target));
            return;
            case 3:
            this.label1 = ((System.Windows.Controls.Label)(target));
            return;
            case 4:
            this.label2 = ((System.Windows.Controls.Label)(target));
            return;
            case 5:
            this.AddStatusEffectButton = ((System.Windows.Controls.Button)(target));
            
            #line 12 "..\..\..\..\Popups\AddStatusEffect.xaml"
            this.AddStatusEffectButton.Click += new System.Windows.RoutedEventHandler(this.AddStatusEffect_Click);
            
            #line default
            #line hidden
            return;
            case 6:
            this.CancelAddStatusEffectButton = ((System.Windows.Controls.Button)(target));
            
            #line 13 "..\..\..\..\Popups\AddStatusEffect.xaml"
            this.CancelAddStatusEffectButton.Click += new System.Windows.RoutedEventHandler(this.CancelAddStatusEffect_Click);
            
            #line default
            #line hidden
            return;
            case 7:
            this.AddStatusEffectNameBox = ((System.Windows.Controls.TextBox)(target));
            return;
            case 8:
            this.AddStatusEffectValueBox = ((System.Windows.Controls.TextBox)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

