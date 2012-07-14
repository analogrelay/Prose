using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Prose.Events;
using Prose.Structure;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Prose.Test.App
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private static readonly SolidColorBrush brush = new SolidColorBrush(Colors.Yellow);
        private Run _currentlySelected;
        private Brush _oldBrush;

        public MainPage()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
        }

        private void Decrease_Click(object sender, RoutedEventArgs e)
        {
            if (Viewer.ColumnWidth >= 50)
            {
                Viewer.ColumnWidth -= 50;
            }
            //SizeBlock.Text = String.Format("Column Width: {0}", Viewer.ColumnWidth);
        }

        private void Increase_Click(object sender, RoutedEventArgs e)
        {
            Viewer.ColumnWidth += 50;
            //SizeBlock.Text = String.Format("Column Width: {0}", Viewer.ColumnWidth);
        }

        public void ProseDoc_PointerMoved(object sender, PointerTextEventArgs args)
        {
            if (args.OriginalSource is Run)
            {
                Run r = args.TextPointer.Node as Run;
                if (r != null)
                {
                    if (_currentlySelected != null)
                    {
                        _currentlySelected.Foreground = _oldBrush;
                    }
                    _currentlySelected = r;
                    _oldBrush = r.Foreground;
                    r.Foreground = brush;
                    CursorLoc.Text = String.Format("Character Offset: {0}, Text: {1}", args.TextPointer.GlobalOffset, r.Text.Length > 10 ? (r.Text.Substring(0, 10) + "...") : r.Text);
                }
            }
        }
    }
}
