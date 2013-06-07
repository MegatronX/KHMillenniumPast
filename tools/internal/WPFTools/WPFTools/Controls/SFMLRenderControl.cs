using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using SFML.Graphics;
namespace WPFTools.Controls
{
    public delegate void RenderControlDrawing(SFMLRenderControl control);
    public partial class SFMLRenderControl : UserControl
    {
        Thread DrawThread;
       
        public event RenderControlDrawing Drawing;
        public RenderWindow Window
        {
            get;
            set;
        }
        public List<Sprite> DrawableSprites
        {
            get;
            set;
        }
        public SFML.Graphics.Color ClearColor
        {
            get;
            set;
        }
        public SFML.Graphics.Shader GlobalShader
        {
            get;
            set;
        }
        public bool DrawWindow
        {
            get;
            set;
        }
        public object DrawLocked
        {
            get;
            private set;
        }
        public void DispatchDrawing()
        {
            if (Drawing != null)
                Drawing(this);
        }
        public SFMLRenderControl() : this(30, 300, 375)
        {

        }
        int FrameTime = 16;
        public SFMLRenderControl(uint fps, int width, int height)
        {
            InitializeComponent();
            this.Width = width;
            this.Height = height;
            Window = new RenderWindow(this.Handle);
            Window.SetFramerateLimit(fps);
            DrawableSprites = new List<Sprite>();

            SetStyle(ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque, true);
            FrameTime = (int)(1000.0f / (float)fps);
            ClearColor = SFML.Graphics.Color.Black;
            DrawWindow = true;
            DrawLocked = new object();
            DrawThread = new Thread(DrawLoop);
            DrawThread.Start();
            RedrawWindow();
        }

        private void DrawLoop()
        {
            while (DrawWindow)
            {
                //RedrawWindow();
                this.Invalidate();
                Thread.Sleep(FrameTime);
            }
        }

        private void RedrawWindow()
        {
            Window.DispatchEvents();
            lock (DrawLocked)
            {
                DispatchDrawing();
                Window.Clear(ClearColor);

                foreach (var sprite in DrawableSprites)
                {
                    if (GlobalShader != null)
                        Window.Draw(sprite, GlobalShader);
                    else
                        Window.Draw(sprite);
                }
                Window.Display();
               // this.RedrawWindow();
               
            }
            
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            RedrawWindow();
            //RedrawWindow();
           
           // this.Invalidate();
        }
    }
}
