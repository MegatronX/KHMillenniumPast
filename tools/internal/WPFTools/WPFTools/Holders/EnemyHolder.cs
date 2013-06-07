using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data;
using System.Data.Common;

namespace WPFTools.Holders
{
    public class EnemyHolder
    {
        int EnemyId { get; set; }
        public string Name { get; set; }
        public DataSet BasicInfoDataSet { get; set; }
        public DataSet StatDataSet { get; set; }
    }
}
