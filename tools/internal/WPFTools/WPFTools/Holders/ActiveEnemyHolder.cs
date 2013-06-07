using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ComponentModel;

namespace WPFTools.Holders
{
    class ActiveEnemyHolder : INotifyPropertyChanged
    {
        string name;
        EnemyHolder eHolder;

        public event PropertyChangedEventHandler PropertyChanged;

        public EnemyHolder EnemyHolder
        {
            get { return eHolder; }
            set
            {
                eHolder = value;
                if (eHolder != null)
                {
                    name = eHolder.Name;
                    OnPropertyChanged("Name");
                }
            }
           
        }
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
                OnPropertyChanged("Name");
            }
        }

        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
                handler(this, new PropertyChangedEventArgs(name));
        }

    }
}
