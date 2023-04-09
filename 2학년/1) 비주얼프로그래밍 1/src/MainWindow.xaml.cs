using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Reflection;
using System.Windows.Media.Animation;
using System.Runtime.InteropServices;   // 마우스 클릭 이벤트
using System.Media;
using System.Windows.Markup.Localizer;
using System.Security.Cryptography.X509Certificates;

namespace FIND
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            UploadImage();
        }

        


        private static DateTime Delay(int MS)
        {
            DateTime ThisMoment = DateTime.Now;
            TimeSpan duration = new TimeSpan(0, 0, 0, 0, MS);
            DateTime AfterWards = ThisMoment.Add(duration);

            while (AfterWards >= ThisMoment)
            {
                ThisMoment = DateTime.Now;
            }
            return DateTime.Now;
        }

        public int level = 0;
        public int[] cnt = { 5, 5, 7, 7 };
        public bool[] map1 = { false, false, false, false, false };
        public int[] map1_SX = { -115, 211, 298, 7, 324 };
        public int[] map1_SY = { -126, 126, 104, 250, 275 };
        public int[] map1_EX = { 149, 256, 336, 140, 370 };
        public int[] map1_EY = { 165, 163, 130, 312, 314 };

        public bool[] map2 = { false, false, false, false, false };
        public int[] map2_SX = { 104, 105, 214, 254, 254 };
        public int[] map2_SY = { 280, 169, 88, 85, 192 };
        public int[] map2_EX = { 128, 118, 228, 280, 277 };
        public int[] map2_EY = { 308, 184, 107, 122, 215 };

        public bool[] map3 = { false, false, false, false, false, false, false };
        public int[] map3_SX = { 173, 262, 206, 152, 145, 158, 258 };
        public int[] map3_SY = { 122, 88, 176, 223, 192, 209, 304 };
        public int[] map3_EX = { 187, 286, 222, 170, 157, 181, 272 };
        public int[] map3_EY = { 130, 105, 206, 233, 198, 316, 315 };

        public bool[] map4 = { false, false, false, false, false, false, false };
        public int[] map4_SX = { 95, 261, 211, 289, 69, 210, 181 };
        public int[] map4_SY = { 123, 104, 149, 168, 234, 276, 293 };
        public int[] map4_EX = { 106, 290, 220, 305, 95, 232, 196 };
        public int[] map4_EY = { 136, 139, 164, 188, 255, 291, 306 };


        public async void UploadImage()
        {

            while (true)
            {
                if (level == 0)
                {
                    image1.Source = new BitmapImage(new Uri(string.Format("{0}.png", 1), UriKind.Relative));
                    image2.Source = new BitmapImage(new Uri(string.Format("{0}.png", 2), UriKind.Relative));
                    await Task.Delay(30);
                }
                else if (level == 1)
                {
                    image1.Source = new BitmapImage(new Uri(string.Format("{0}.png", 3), UriKind.Relative));
                    image2.Source = new BitmapImage(new Uri(string.Format("{0}.png", 4), UriKind.Relative));
                    await Task.Delay(30);
                }
                else if (level == 2)
                {
                    image1.Source = new BitmapImage(new Uri(string.Format("{0}.png", 5), UriKind.Relative));
                    image2.Source = new BitmapImage(new Uri(string.Format("{0}.png", 6), UriKind.Relative));
                    await Task.Delay(30);
                }
                else
                {
                    image1.Source = new BitmapImage(new Uri(string.Format("{0}.png", 7), UriKind.Relative));
                    image2.Source = new BitmapImage(new Uri(string.Format("{0}.png", 8), UriKind.Relative));
                    await Task.Delay(30);
                }
            }

        }

        private void ProgressBar_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        // 타이머
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Duration timeFlow = new Duration(TimeSpan.FromSeconds(100));
            DoubleAnimation barAnimate = new DoubleAnimation(ProgressBar1.Value + 100, timeFlow);
            ProgressBar1.BeginAnimation(ProgressBar.ValueProperty, barAnimate);
        }

        public void passLv(bool[] map)
        {
            int cnt = 0;
            for (; cnt < map.Length; cnt++)
            {
                if (map[cnt] == false)
                {
                    return;
                }
            }
            level++;
        }
        

        public void failSound()
        {
            //MessageBox.Show(System.IO.Directory.GetCurrentDirectory());
            SoundPlayer Do = new SoundPlayer("../../music/fail.wav");
            Do.Play();
        }

        public void isCorrect(double x, double y)
        {
            if(level == 0)
            {
                bool ps = false;
                for (int i = 0; i < map1_EX.Length; i++)
                {
                    if(map1_SX[i] <= x && map1_SY[i] <= y && x<= map1_EX[i] && y<= map1_EY[i])
                    {
                        SoundPlayer Do = new SoundPlayer("../../music/dingdong.wav");
                        Do.Play();
                        MessageBox.Show("찾았다!");
                        ps = map1[i] = true;
                        passLv(map1);
                        break;
                    }
                }
                if (!ps) failSound();
            }
            else if (level == 1)
            {
                bool ps = false;
                for (int i = 0; i < map2_EX.Length; i++)
                {
                    if (map2_SX[i] <= x && map2_SY[i] <= y && x <= map2_EX[i] && y <= map2_EY[i])
                    {
                        SoundPlayer Do = new SoundPlayer("../../music/dingdong.wav");
                        Do.Play();
                        MessageBox.Show("찾았다!");
                        ps = map2[i] = true;
                        passLv(map2);
                        break;
                    }
                }
                if (!ps) failSound();
            }
            else if(level == 2)
            {
                bool ps = false;
                for (int i = 0; i < map3_EX.Length; i++)
                {
                    if (map3_SX[i] <= x && map3_SY[i] <= y && x <= map3_EX[i] && y <= map3_EY[i])
                    {
                        SoundPlayer Do = new SoundPlayer("../../music/dingdong.wav");
                        Do.Play();
                        MessageBox.Show("찾았다!");
                        ps = map3[i] = true;
                        passLv(map3);
                        break;
                    }
                }
                if (!ps) failSound();
            }
            else if (level == 3)
            {
                bool ps = false;
                for (int i = 0; i < map4_EX.Length; i++)
                {
                    if (map4_SX[i] <= x && map4_SY[i] <= y && x <= map4_EX[i] && y <= map4_EY[i])
                    {
                        SoundPlayer Do = new SoundPlayer("../../music/dingdong.wav");
                        Do.Play();
                        MessageBox.Show("찾았다!");
                        ps = map4[i] = true;
                        passLv(map4);
                        break;
                    }
                }
                if (!ps) failSound();
            }
            else
            {
                MessageBox.Show("게임종료");
            }
        }


        // 마우스 클릭
        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            DragDrop.DoDragDrop((DependencyObject)e.Source, "Sample", DragDropEffects.Copy);
            System.Windows.Point p1 = Mouse.GetPosition(this);
            isCorrect(p1.X, p1.Y);
            lblInfo1.Content = string.Format("Mouse : {0}, {1}", p1.X, p1.Y);
        }

        // 마우스 드래그
        private void Window_DragOver(object sender, DragEventArgs e)
        {
            System.Windows.Point p2 = e.GetPosition(this);
            lblInfo2.Content = string.Format("Drag : {0}, {1}", p2.X, p2.Y);
        }
    }
}
