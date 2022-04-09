using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;
using System.Resources;
using System.IO;

using System.Threading;
using System.Globalization;

namespace wasilewskijWinForms
{
    public enum Lang
    {
        POL, ENG
    }
    public partial class Form1 : Form
    {
        public class Vertex
        {
            public int x { get; set; }
            public int y { get; set; }
            public int number { get; set; }
            public Color color { get; set; }
            public List<Vertex> neighbors;
            public bool marked { get; set; } = false;
            public Vertex(int x, int y, int nr, Color c)
            {
                this.x = x;
                this.y = y;
                this.number = nr;
                this.color = c;
                neighbors = new List<Vertex>();
            }
            public bool comes(int x, int y)
            {
                return Math.Sqrt((Math.Pow(this.x - x, 2) + Math.Pow(this.y - y, 2))) < 2* (RADIUS + PENSIZE);
            }
            public override string ToString()
            {

                return $"{x} {y} {number} {color.ToArgb()}";
            }
        }
        List<Vertex> VertexList = new List<Vertex>();
        private Bitmap drawArea;
        private const int RADIUS = 20;
        private const int PENSIZE = 4;
        private int vertcount = 1;
        private Pen pen;
        private Pen LinePen;
        private Pen RemoveLinePen;
        private SolidBrush brs;
        Vertex markedvert = null;
        private int Mousex = 0;
        private int Mousey = 0;
        private int Markx = 0;
        private int Marky = 0;
        private bool movingvert = false;

        // For languages:
        private readonly ComponentResourceManager rsc;
        Lang language;
        public Form1()
        {
            Thread.CurrentThread.CurrentUICulture = new CultureInfo("pL-PL");
            InitializeComponent();
            drawArea = new Bitmap(Canvas.Size.Width, Canvas.Size.Height);
            Canvas.Image = drawArea;
            using (Graphics g = Graphics.FromImage(drawArea))
            {
                g.Clear(Color.White);
                pen = new Pen(Brushes.Black, PENSIZE);
                brs = new SolidBrush(Color.Black);
                VertexList = new List<Vertex>();
                LinePen = new Pen(Brushes.Black, PENSIZE);
                RemoveLinePen = new Pen(Brushes.White, PENSIZE);
                language = Lang.POL;
            }
            rsc = new ComponentResourceManager(typeof(Form1));
        }

        private void colorDialog_click(object sender, EventArgs e)
        {
            ColorDialog colorDialog = new ColorDialog();
            if (colorDialog.ShowDialog() == DialogResult.OK)
            {
                tableLayoutPanel3.GetControlFromPosition(1, 0).BackColor = colorDialog.Color;
                pen = new Pen(colorDialog.Color, PENSIZE);
                brs = new SolidBrush(colorDialog.Color);
                if (markedvert != null)
                {
                    markedvert.color = colorDialog.Color;

                    PaintVertAgain(markedvert, true);
                    Canvas.Refresh();
                }
            }
        }
        private void PaintVertAgain(Vertex vertex, bool marked = false)
        {
            StringFormat stringFormat = new StringFormat()
            {
                Alignment = StringAlignment.Center,
                LineAlignment = StringAlignment.Center
            };
            using (Graphics g = Graphics.FromImage(drawArea))
            {
                Pen pen1 = new Pen(vertex.color, PENSIZE);
                if (marked)
                    pen1.DashPattern = new float[] { 3, 1 };
                SolidBrush brs1 = new SolidBrush(vertex.color);
                g.FillEllipse(Brushes.White, vertex.x - RADIUS - PENSIZE, vertex.y - RADIUS - PENSIZE, (RADIUS + PENSIZE) * 2, (RADIUS + PENSIZE) * 2);
                g.DrawEllipse(pen1, vertex.x - RADIUS, vertex.y - RADIUS, RADIUS * 2, RADIUS * 2);
                PointF ff = new PointF(vertex.x, vertex.y);
                FontFamily fontFamily = new FontFamily("Arial");
                Font font = new Font(
                   fontFamily,
                   14,
                   FontStyle.Bold,
                   GraphicsUnit.Pixel);
                g.DrawString((vertex.number).ToString(), font, brs1, ff, stringFormat);
            }
        }
        private void MakeConnection(Vertex from, Vertex to)
        {
            using (Graphics g = Graphics.FromImage(drawArea))
            {
                g.DrawLine(LinePen, new Point(from.x, from.y), new Point(to.x, to.y));
                PaintVertAgain(from);
                PaintVertAgain(to);
                return;
            }
        }
        private void resize(object sender, EventArgs e)
        {
            RedrawFull(true);
            Canvas.Refresh();
        }
        private void RemoveVertex(ref Vertex vertex)
        {

            int nr = vertex.number;
            vertcount--;
            VertexList.RemoveAll((n) => n.number == nr);
            foreach (var vv in VertexList)
                vv.neighbors.RemoveAll((x) => x.number == nr);
            foreach (var ver in VertexList)
            {
                if (ver.number > nr)
                    ver.number--;
            }

            RedrawFull();
            vertex.marked = false;
            vertex = null;
        }
        private void RedrawFull(bool size = false)
        {
            if (size)
            {
                drawArea = new Bitmap(Canvas.Size.Width, Canvas.Size.Height);
                Canvas.Image = drawArea;
            }
            using (Graphics g = Graphics.FromImage(drawArea))
            {
                g.Clear(Color.White);
            }
            foreach (var vertex in VertexList)
            {
                foreach (var vv in vertex.neighbors)
                    MakeConnection(vertex, vv);
            }
            foreach (var vertex in VertexList)
            {
                PaintVertAgain(vertex, vertex.marked);
            }
        }
        private void RemoveVertexButton_Click(object sender, EventArgs e)
        {

            RemoveVertex(ref markedvert);
            RemoveVertexButton.Enabled = false;
            Canvas.Refresh();
        }

        private void ClearGraphButton_Click(object sender, EventArgs e)
        {
            VertexList.Clear();
            vertcount = 1;
            RedrawFull();
            if (markedvert != null)
                markedvert.marked = false;
            markedvert = null;
            RemoveVertexButton.Enabled = false;
            Canvas.Refresh();
        }
        private void MoveVert(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle && markedvert != null)
            {
                movingvert = true;
                Mousex = e.X;
                Mousey = e.Y;
                Markx = markedvert.x;
                Marky = markedvert.y;
            }
            if (e.Button == MouseButtons.Left)
            {
                foreach (var ver in VertexList)
                    if (ver.comes(e.X, e.Y))
                    {
                        if (markedvert == null) return;
                        foreach (var nqh in markedvert.neighbors)
                            if (nqh.number == ver.number)
                            {
                                markedvert.neighbors.RemoveAll((x) => x.number == ver.number);
                                ver.neighbors.RemoveAll((x) => x.number == markedvert.number);
                                RedrawFull();
                                PaintVertAgain(markedvert, true);
                                Canvas.Refresh();
                                return;
                            }
                        using (Graphics g = Graphics.FromImage(drawArea))
                        {
                            markedvert.neighbors.Add(ver);
                            ver.neighbors.Add(markedvert);

                            RedrawFull();
                            PaintVertAgain(markedvert, true);
                            Canvas.Refresh();
                            return;
                        }
                    }
                StringFormat stringFormat = new StringFormat()
                {
                    Alignment = StringAlignment.Center,
                    LineAlignment = StringAlignment.Center
                };
                using (Graphics g = Graphics.FromImage(drawArea))
                {
                    g.FillEllipse(Brushes.White, e.X - RADIUS - PENSIZE, e.Y - RADIUS - PENSIZE, (RADIUS + PENSIZE) * 2, (RADIUS + PENSIZE) * 2);
                    g.DrawEllipse(pen, e.X - RADIUS, e.Y - RADIUS, RADIUS * 2, RADIUS * 2);
                    PointF ff = new PointF(e.X, e.Y);
                    FontFamily fontFamily = new FontFamily("Arial");
                    Font font = new Font(
                       fontFamily,
                       14,
                       FontStyle.Bold,
                       GraphicsUnit.Pixel);
                    VertexList.Add(new Vertex(e.X, e.Y, vertcount, pen.Color));
                    g.DrawString((vertcount++).ToString(), font, brs, ff, stringFormat);
                }
                Canvas.Refresh();
            }
            if (e.Button == MouseButtons.Right)
            {
                if (markedvert != null)
                {
                    markedvert.marked = false;
                    PaintVertAgain(markedvert);
                }

                bool exist = false;
                foreach (var ver in VertexList)
                    if (ver.comes(e.X, e.Y))
                    {
                        markedvert = ver;
                        markedvert.marked = true;
                        exist = true;
                        RemoveVertexButton.Enabled = true;
                        break;
                    }
                if (exist == false)
                {
                    if (markedvert != null)
                        markedvert.marked = false;
                    markedvert = null;
                    RemoveVertexButton.Enabled = false;
                    Canvas.Refresh();
                    return;
                }
                PaintVertAgain(markedvert, true);
                Canvas.Refresh();
            }

        }
        private void Delmovevert(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle)
            {
                movingvert = false;
            }

        }
        private void MoveVertex(object sender, MouseEventArgs e)
        {
            if (movingvert == true)
            {
                Pen pen1 = new Pen(Brushes.White, PENSIZE);
                using (Graphics g = Graphics.FromImage(drawArea))
                {
                    g.Clear(Color.White);
                    foreach (var vertex in VertexList)
                    {
                        foreach (var vv in vertex.neighbors)
                        {
                            g.DrawLine(pen1, new Point(markedvert.x, markedvert.y), new Point(vv.x, vv.y));
                            PaintVertAgain(markedvert);
                            PaintVertAgain(vv);
                        }
                    }
                    foreach (var vertex in VertexList)
                    {
                        PaintVertAgain(vertex, vertex.marked);
                    }
                }
                markedvert.x = Markx + e.X - Mousex;
                markedvert.y = Marky + e.Y - Mousey;
                RedrawFull();
                Canvas.Refresh();
            }
        }
        private void POLbutton_Click(object sender, EventArgs e)
        {
            language = Lang.POL;
            Thread.CurrentThread.CurrentUICulture = new CultureInfo("pl-PL");
            rsc.ApplyResources(this, "$this");
            RecApply(rsc, this.Controls);
            if (markedvert != null)
                RemoveVertexButton.Enabled = true;
        }
        private void RecApply(ComponentResourceManager resources, Control.ControlCollection controls)
        {
            foreach (Control control in controls)
            {
                resources.ApplyResources(control, control.Name);
                RecApply(resources, control.Controls);
            }
        }
        private void ENGbutton_Click(object sender, EventArgs e)
        {
            language = Lang.ENG;
            Thread.CurrentThread.CurrentUICulture = new CultureInfo("en-001");
            rsc.ApplyResources(this, "$this");
            RecApply(rsc, this.Controls);
            if (markedvert != null)
                RemoveVertexButton.Enabled = true;

        }
        private class Edges
        {
            public int from, to;
            public Edges(int f, int t)
            {
                from = f;
                to = t;
            }
            public override string ToString()
            {
                return $"{from} {to}";
            }
        }
        private void SaveButton_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveGraph = new SaveFileDialog();
            saveGraph.Filter = "Graph File|*.graph";
            saveGraph.Title = language == Lang.POL ? "Zapisz Graf" : "Save Graph";
            if (saveGraph.ShowDialog() == DialogResult.OK)
            {
                string zapis = "";
                foreach (Vertex ver in VertexList)
                    zapis += ver.ToString() + "\n";

                File.WriteAllText(saveGraph.FileName, zapis);
                List<Edges> edgelist = new List<Edges>();
                File.AppendAllText(saveGraph.FileName, "\n");
                foreach (Vertex ver in VertexList)
                {
                    foreach (Vertex ngh in ver.neighbors)
                    {
                        if (edgelist.FindIndex((x) => ((x.from == ver.number && x.to == ngh.number) || x.to == ver.number && x.from == ngh.number)) == -1)
                        {
                            edgelist.Add(new Edges(ver.number, ngh.number));
                        }
                    }
                }
                var edges = "";
                foreach (var e1 in edgelist)
                    edges += e1.ToString() + "\n";
                File.AppendAllText(saveGraph.FileName, edges);
                MessageBox.Show(language == Lang.POL ? " Graf zapisano pomyślnie" : "Correctly saved Graph");
            }
        }
        private void ClearGraph()
        {
            VertexList.Clear();
            vertcount = 1;
            RedrawFull();
            if (markedvert != null)
                markedvert.marked = false;
            markedvert = null;
            RemoveVertexButton.Enabled = false;
        }
        private void ReadButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog openGraph = new OpenFileDialog();
            openGraph.Filter = "Graph File|*.graph";
            openGraph.Title = language == Lang.POL ? "Wczytaj Graf" : "Read Graph";
            if (openGraph.ShowDialog() == DialogResult.OK)
            {
                string read = File.ReadAllText(openGraph.FileName);
                var verts = read.Split('\n');
                ClearGraph();
                if (read.Any(x => char.IsLetter(x)))
                {
                    MessageBox.Show(language == Lang.POL ? "Wadliwy Plik" : "Bad FiLe");
                    ClearGraph();
                    return;
                }
                int idx = 0;
                foreach (var verinfo in verts)
                {
                    if (verinfo.Equals("")) break;
                    var tableinfo = verinfo.Split(' ');
                    if(tableinfo.Length!=4)
                    {
                        MessageBox.Show(language == Lang.POL ? "Wadliwy Plik" : "Bad FiLe");
                        ClearGraph();
                        return;
                    }
                    VertexList.Add(new Vertex(int.Parse(tableinfo[0]), int.Parse(tableinfo[1]), int.Parse(tableinfo[2]), Color.FromArgb(int.Parse(tableinfo[3]))));
                    vertcount++;
                    idx++;
                }
                for(int i = idx+1;i<verts.Length-1;i++)
                {
                    if (verts[i].Equals(""))
                    {
                        MessageBox.Show(language == Lang.POL ? "Wadliwy Plik" : "Bad FiLe");
                        ClearGraph();
                        return;
                    }
                    var edge = verts[i].Split(' ');
                    if(edge.Length!=2)
                    {
                        MessageBox.Show(language == Lang.POL ? "Wadliwy Plik" : "Bad FiLe");
                        ClearGraph();
                        return;
                    }
                    int from = int.Parse(edge[0]);
                    int to = int.Parse(edge[1]);
                    foreach (var ver in VertexList)
                    {
                        if (ver.number == from)
                            ver.neighbors.Add(VertexList.Find((x) => x.number == to));
                        if (ver.number == to)
                            ver.neighbors.Add(VertexList.Find((x) => x.number == from));
                    }
                }
                foreach (Vertex v in VertexList)
                    v.marked = false;
                markedvert = null;
                movingvert = false;
                RedrawFull();
                Canvas.Refresh();
            }
        }

        private void dellpress(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Delete && markedvert !=null)
            {
                RemoveVertex(ref markedvert);
                RemoveVertexButton.Enabled = false;
                Canvas.Refresh();
            }
        }
    }
}
