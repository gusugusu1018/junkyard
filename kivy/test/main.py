from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.config import Config
from kivy.uix.slider import Slider
from kivy.uix.actionbar import ActionBar, ActionItem, ActionButton, ActionView, ActionPrevious, ActionGroup
from kivy.uix.floatlayout import FloatLayout
import tkinter, tkinter.filedialog, tkinter.messagebox
import numpy as np
import matplotlib
matplotlib.use('module://kivy.garden.matplotlib.backend_kivy')
import matplotlib.pyplot as pl
import sys, os

class GraphView(BoxLayout):
    def __init__(self, **kwargs):
        super(GraphView, self).__init__(orientation='vertical')
        self.label=Label(text="Please slide the slider")
        self.add_widget(self.label)
        self.slider = Slider(min=-2, max=2, value=1)
        self.slider.bind(value=self.SliderCallback)
        self.add_widget(self.slider)
        self.add_widget(self.graph_plot_sample(self.slider.value))
        actionview = ActionView()
        actionview.use_separator=True
        ap = ActionPrevious(title='Dawot', with_previous=False) 
        actionview.add_widget(ap) 
        self.abtn1=ActionButton(text="File")
        self.abtn1.bind(on_press=self.ActionBtn1Callback)
        actionview.add_widget(self.abtn1) 
        self.abtn2=ActionButton(text="Plot")
        self.abtn2.bind(on_press=self.ActionBtn2Callback)
        actionview.add_widget(self.abtn2) 
        self.actionbar=ActionBar()
        self.actionbar.add_widget(actionview)
        self.add_widget(self.actionbar)

    def SliderCallback(self,instance,value):
        self.label.text=str(value)

    def ActionBtn1Callback(self,instance):
        root = tkinter.Tk()
        root.withdraw()
        fTyp = [("","*")]
        iDir = os.path.abspath(os.path.dirname(__file__))
        file = tkinter.filedialog.askopenfilename(filetypes = fTyp,initialdir = iDir)
        tkinter.messagebox.showinfo('Input file',file)

    def ActionBtn2Callback(self,instance):
        self.graph_plot_sample(self.slider.value)

    def graph_plot_sample(self, value):
        fig, ax = pl.subplots()
        x = np.linspace(-np.pi, np.pi)
        print(type(value))
        print(value)
        y = np.sin(x*float(value))
        #y = np.sin(x*2.0)
        ax.set_xlabel("X label")
        ax.set_ylabel("Y label")
        ax.grid(True)
        ax.plot(x, y)
        pl.draw()
        fig.canvas.draw()
        return fig.canvas

class TestApp(App):
    def build(self):
        self.title = 'My Test'
        #self.icon = 'icon.jpeg'
        height = 500
        Config.set('graphics', 'height', height)
        Config.set('graphics', 'width', height * 3)
        return GraphView()

if __name__ == '__main__':
    TestApp().run()