   M S B A M L   `   `   `  ����  WPFToolsH    BWPFTools.ComponentControls.ItemComponents.SynthesisRecipeComponent   5      W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35H 9http://schemas.microsoft.com/winfx/2006/xaml/presentation      5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      Hmc;http://schemas.openxmlformats.org/markup-compatibility/2006    5      >d2http://schemas.microsoft.com/expression/blend/2008    5      -   5        $)��#SynthesisRecipeComponentUserControl��5   7   .��5      �   � DataContext  5	   
   �� 5
       �� ElementName$) #SynthesisRecipeComponentUserControl��6    �� Path$ RootComponentElement�6H   .+�5      �� -   5        $��RequirementsGroupBox��5   d   $��Requirements��6   $	��296��6*   $
��Left=�67   $��0,34,0,0q�6R   $	��Top=�6�   $	��405��6�   .��5      � .+�5      �� -   5        $��RequiredItemsBox��5   m   $��Required Items��6   $	��151��63   $
��Left=�6@   $��-1,0,0,0q�6[   $	��Top=�6�   $	��397��6�   .��5      � .+�5      �� -   5        $��EnemyStatViewDisplay��5   T   $
��Left=�6p   $	��384��6�   $��0,6,0,0q�6�   ��6#   ��  �� XPath$ RequiredItems/Item�� � ContextMenu 5      �� 5   "   -   5        $��RequiredItemsConextBox��5   ?    J� 	AllowDrop . .@�5   &   m� -   5        $��AddNewRequiredItem��5   y   $��Add New Item��6/    � ToolTip$/ )Opens a window to add a new required item��6E   6y   m� 5   &   -   5        $��RemoveRequiredItem��5   f   $��Remove Current��6/   $ Removes Current Item��6G   6f   5   #    �� View 5      �� 5   "   .P�5   &   ��  �� Width$	 250��65   $��	Item Name��6A   	 �� CellTemplate	 5   *   �� 5   .   .R�5   2   � .+�5   6   �� $	��250��6@   ��6L   �� $ @name��5   3   5   /   5!   '   �� 5"   &   $	 100��65   $��
# Required��6A   	 5#   *   �� 5$   .   .R�5%   2   � .+�5&   6   �� $	��100��6>   ��6J   �� $ @count��5'   3   5(   /   5*   '   5+   #   5-      5.      5/      50      51      �� 52   
   -   5        $��label2��52   �   
����iA�$��Synthesis Recipe��6'   $
��Bold"�6B   
�������$��28��6g   $
��Left=�6s   $	��Top=�6�   $	��710��6�   �� 53   
   -	   5        $��OtherRequirementsBox��53   y   $   ��6   $��Other Requirements��6"   $	��128��6>   $
��Left=�6K   $��	6,202,0,0q�6f   $	��Top=�6�   $	��389��6�   .��54      � .+�55      �� -
   5        $��listBox1��55   U   $	��100��6   $
��Left=�6'   $��	256,0,0,0q�6B   $	��Top=�6e   $	��120��6}   �� 56      -   5        $��label1��56   c   $��Others��6   $��28��6)   $
��Left=�65   $��	194,0,0,0q�6P   $	��Top=�6q   �� 57      -   5        $��RemoveReqirementButton��57   e   $��Button��6   $��23��6*   $
��Left=�66   $��
194,59,0,0q�6Q   $	��Top=�6�   $��56��6�   �� 58      -   5        $��AddRequirement��58   e   $��Button��6   $��23��6*   $
��Left=�66   $��
194,30,0,0q�6Q   $	��Top=�6{   $��56��6�   �� 59      -   5        $'��!CharacterLevelRequirementCheckBox��59   m   $��Character Level��6   $��16��65   $
��Left=�6A   $��6,6,0,0q�6\   $	��Top=�6�   �� 5:      -   5        $��RequiredCharacterLevel��5:   �   $��23��6p   $
��Left=�6|   $��	116,3,0,0q�6�   $	��Top=�6�   $��72��6�   {�6   �� $' !CharacterLevelRequirementCheckBox��$ 	IsChecked�6�   �� 5;      -   5        $��SynthesisLevelRequirement��5;   n   $��Synthesis Level��6   $��16��65   $
��Left=�6A   $��6,34,0,0q�6\   $	��Top=�6�   $��98��6�   �� 5<      -   5        $��RequiredSynthesisRank��5<   U   $��23��6   $
��Left=�6&   $��
116,31,0,0q�6A   $	��Top=�6r   $��72��6�   �� 5=      -   5        $��MunnyRequirement��5=   d   $��Munny��6   $��16��6+   $
��Left=�67   $��6,63,0,0q�6R   $	��Top=�6|   $��98��6�   �� 5>      -   5        $��RequiredMunny��5>   U   $��23��6   $
��Left=�6&   $��
116,60,0,0q�6A   $	��Top=�6j   $��72��6�   5?      5@      �� 5A   
   -   5        $��ResultGroup��5A   Y   $��Result Group��6   $��Right=�6)   $��
0,34,3,125q�6E   $	��305��6l   .��5B      � .+�5C      �� -   5        $��label3��5C   k   $��Resulting Items��6   $��28��62   $
��Left=�6>   $��6,-2,0,0q�6Y   $	��Top=�6y   �� 5D      -   5        $��	listView1��5D   z   $
��Left=�6   $��6,24,0,3q�6h   $	��286��6�   ��66   �� $ ResultingItems/Item�� 5E      �� 5F      .P�5G      �� $��	Item Name��6-   $	 200��6@   	 5H   "   �� 5I   &   .R�5J   *   � .+�5K   .   �� $	��200��6U   ��68   �� $ @name��6U   5L   +   5M   '   5O      �� 5P      $��	# Created��6-   $ 90��6@   	 5Q   "   �� 5R   &   .R�5S   *   � .+�5T   .   �� $��80��6T   ��66   �� $ @count��6T   5U   +   5V   '   5X      5Y      5[      5\      5]      �� 5^   
   -   5        $��image1��5^   9   $	��128��6   $��Right=�6   $
��Fill=�6G   $��Bottom=�6V   $	��128��6q   5_      5`      