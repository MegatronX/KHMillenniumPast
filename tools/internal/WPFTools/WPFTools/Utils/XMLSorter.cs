using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.ComponentModel;

namespace WPFTools.Utils
{
    public class TAXmlDocument : XmlDocument
    {
        public enum SortType
        {
            Ascending,
            Descending
        }

        public abstract class TAXmlSorter : IComparer<XmlNode>
        {
            Comparison<XmlNode> comparisonDelegate;
            protected TAXmlSorter(SortType st)
            {
                switch (st)
                {
                    case SortType.Ascending:
                        comparisonDelegate = CompareAsc;
                        break;
                    case SortType.Descending:
                        comparisonDelegate = CompareDesc;
                        break;
                }
            }

            protected abstract int CompareAsc(XmlNode x, XmlNode y);
            protected abstract int CompareDesc(XmlNode x, XmlNode y);

            public abstract void InitArray(XmlNode[] array);

            #region IComparer<XmlNode> Members

            int IComparer<XmlNode>.Compare(XmlNode x, XmlNode y)
            {
                return comparisonDelegate(x, y);
            }

            #endregion
        }

        public sealed class TAXSNodeName : TAXmlSorter
        {
            public TAXSNodeName(SortType st) : base(st) { }
            public TAXSNodeName() : base(SortType.Ascending) { }

            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                return x.Name.CompareTo(y.Name);
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return y.Name.CompareTo(x.Name);
            }

            public override void InitArray(XmlNode[] array)
            {
            }
        }

        public sealed class TAXSNodeAttribute<AttributeType> : TAXmlSorter
            where AttributeType : IComparable, IConvertible
        {
            string attName;
            Dictionary<XmlNode, AttributeType> values;
            public TAXSNodeAttribute(string AttributeName)
                : this(AttributeName, SortType.Ascending)
            {
            }

            public TAXSNodeAttribute(string AttributeName, SortType st)
                : base(st)
            {
                if (string.IsNullOrEmpty(AttributeName))
                    throw new ArgumentNullException("AttributeName");
                attName = AttributeName;
            }

            public override void InitArray(XmlNode[] array)
            {
                values = new Dictionary<XmlNode, AttributeType>();
                TypeConverter tc = TypeDescriptor.GetConverter(typeof(AttributeType));
                foreach (XmlNode n in array)
                {
                    XmlAttribute attr = n.Attributes[attName];
                    if (attr != null)
                    {
                        try
                        {
                            values.Add(n, (AttributeType)tc.ConvertFrom(attr.Value));
                        }
                        catch
                        {
                            values.Add(n, default(AttributeType));
                        }
                    }
                    else
                    {
                        values.Add(n, default(AttributeType));
                    }
                }
            }

            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                return values[x].CompareTo(values[y]);
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return values[y].CompareTo(values[x]);
            }
        }

        public sealed class TAXSChildCount : TAXmlSorter
        {
            public TAXSChildCount() : base(SortType.Ascending) { }
            public TAXSChildCount(SortType st) : base(st) { }

            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                return x.ChildNodes.Count.CompareTo(y.ChildNodes.Count);
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return y.ChildNodes.Count.CompareTo(x.ChildNodes.Count);
            }

            public override void InitArray(XmlNode[] array)
            {
            }
        }

        public sealed class TAXSAttributeCount : TAXmlSorter
        {
            public TAXSAttributeCount() : base(SortType.Ascending) { }
            public TAXSAttributeCount(SortType st) : base(st) { }

            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                return x.Attributes.Count.CompareTo(y.Attributes.Count);
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return y.Attributes.Count.CompareTo(x.Attributes.Count);
            }

            public override void InitArray(XmlNode[] array)
            {
            }
        }

        public sealed class TAXSInnerText : TAXmlSorter
        {
            public TAXSInnerText() : base(SortType.Ascending) { }
            public TAXSInnerText(SortType st) : base(st) { }

            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                return x.InnerText.CompareTo(y.InnerText);
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return y.InnerText.CompareTo(x.InnerText);
            }

            public override void InitArray(XmlNode[] array)
            {
            }
        }

        public sealed class TAXSInnerValue<ValueType> : TAXmlSorter
            where ValueType : IComparable, IConvertible
        {
            Dictionary<XmlNode, ValueType> values;
            public TAXSInnerValue()
                : this(SortType.Ascending)
            {
            }

            public TAXSInnerValue(SortType st)
                : base(st)
            {
            }

            public override void InitArray(XmlNode[] array)
            {
                values = new Dictionary<XmlNode, ValueType>();
                TypeConverter tc = TypeDescriptor.GetConverter(typeof(ValueType));
                foreach (XmlNode n in array)
                {
                    try
                    {
                        values.Add(n, (ValueType)tc.ConvertFrom(n.InnerText));
                    }
                    catch
                    {
                        values.Add(n, default(ValueType));
                    }
                }
            }

            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                return values[x].CompareTo(values[y]);
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return values[y].CompareTo(values[x]);
            }
        }

        public sealed class TAXSMulti : TAXmlSorter
        {
            TAXmlSorter[] sorters;
            public TAXSMulti(params TAXmlSorter[] _s)
                : base(SortType.Ascending)
            {
                if (_s == null || _s.Length == 0)
                    throw new ArgumentNullException("_s");
                sorters = _s;
            }
            protected override int CompareAsc(XmlNode x, XmlNode y)
            {
                foreach (TAXmlSorter s in sorters)
                {
                    int i = ((IComparer<XmlNode>)s).Compare(x, y);
                    if (i != 0)
                        return i;
                }
                return 0;
            }

            protected override int CompareDesc(XmlNode x, XmlNode y)
            {
                return 0;
            }

            public override void InitArray(XmlNode[] array)
            {
                foreach (TAXmlSorter s in sorters)
                    s.InitArray(array);
            }
        }


        public TAXmlDocument() : base() { }
        public TAXmlDocument(XmlImplementation imp) : base(imp) { }
        public TAXmlDocument(XmlNameTable nt) : base(nt) { }

        public void Sort(XmlNode parentNode, TAXmlSorter sorter)
        {
            if (parentNode == null)
                throw new ArgumentNullException("parentNode");
            if (sorter == null)
                throw new ArgumentNullException("sorter");
            if (parentNode.OwnerDocument != this)
                throw new Exception("parentNode value is not child of this document");
            //if childcount less than 2 then it is not necessary to sort
            if (parentNode.ChildNodes.Count < 2)
                return;
            //copy the childs of parent
            XmlNode[] nodes = new XmlNode[parentNode.ChildNodes.Count];
            for (int i = 0; i < nodes.Length; i++)
                nodes[i] = parentNode.ChildNodes[i];

            //call abstract initarray method of sorter
            sorter.InitArray(nodes);

            //call array.sort to sort nodes
            Array.Sort(nodes, sorter);

            //remove all child nodes of parent
            parentNode.InnerXml = "";

            //add sorted nodes
            for (int i = 0; i < nodes.Length; i++)
                parentNode.AppendChild(nodes[i]);
        }


        //Added by Andrew Chudley
        //29 Jan 09
        //Code Project Profile : 
        //http://www.codeproject.com/script/Membership/Profiles.aspx?mid=1677998

        public void Sort(XmlNodeList nodelist, TAXmlSorter sorter)
        {

            try
            {
                if (nodelist == null)
                    throw new ArgumentNullException("nodelist");
                if (nodelist.Count == 0)
                    throw new ArgumentNullException("nodelist empty");
                if (sorter == null)
                    throw new ArgumentNullException("sorter");
                if (nodelist[0].OwnerDocument != this)
                    throw new Exception("nodelist is not child of this document");
                //if childcount less than 2 then it is not necessary to sort
                if (nodelist.Count < 2)
                    return;
                //copy the children
                XmlNode[] nodes = new XmlNode[nodelist.Count];
                for (int i = 0; i < nodes.Length; i++)
                    nodes[i] = nodelist[i];

                //call abstract initarray method of sorter
                sorter.InitArray(nodes);

                //call array.sort to sort nodes
                Array.Sort(nodes, sorter);

                XmlNode grandparentNode = nodelist[0].ParentNode.ParentNode;

                //remove all child nodes of grandparent
                grandparentNode.InnerXml = "";

                //add parents of the sorted nodes
                for (int i = 0; i < nodes.Length; i++)
                    grandparentNode.AppendChild(nodes[i].ParentNode);

            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.Write(ex.Message);

            }

        }

    }
}
