   M S B A M L   `   `   `  ���� R  NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35L5clr-namespace:System.Diagnostics;assembly=WindowsBaseSystem.Diagnostics  C ?WPFTools, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null- clr-namespace:Wpf.Util;assembly=Wpf.Util q mSystem.Windows.Controls.Layout.Toolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35qUclr-namespace:System.Windows.Controls;assembly=System.Windows.Controls.Layout.ToolkitSystem.Windows.Controls    WPFTools.Editor   W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35H 9http://schemas.microsoft.com/winfx/2006/xaml/presentation       8x,http://schemas.microsoft.com/winfx/2006/xaml     Edebug5clr-namespace:System.Diagnostics;assembly=WindowsBase     /util clr-namespace:Wpf.Util;assembly=     bmyUclr-namespace:System.Windows.Controls;assembly=System.Windows.Controls.Layout.Toolkit     -   $��KHMPToolsWindow��  � Title$  Kingdom Hearts MP Tools��$	��700��$
��1000�� � 	Resources    EnemyDB � XPath � IsAsynchronous,   &System.Windows.Data.DataSourceProvider   IsInitialLoadEnabled1   +System.Diagnostics.PresentationTraceSources   
TraceLevel 
 ItemDB��%w   &	        &	 3     � $ /Enemies/Enemy�� .   . $
 High=�� $ /Items/Item�� .   . $
 High=�.��� .+��� -   $��
EditorTabs��.@��� -   $��	GameFiles��$��
Game Files��.��� -   $��GameFilesTabGrid��$	��636��$	��974��.+��� -   $��label9��$��28��$
��Left=�$��	17,53,0,0q�$	��Top=�$	��120��.��Enemies XML File�� -   $��EnemyDBFile��$��23��$��143,55,483,0q�$	��Top=��� -   $��BrowseForEnemyXML��$��23��$��416,84,483,0q�$	��Top=�.��Browse�� -   $��label10��$��28��$
��Left=�$��
17,111,0,0q�$	��Top=�$	��120��.��Items XML File�� -	   $��ItemsDBFile��$��23��$��143,113,483,0q�$	��Top=��� -
   $��BrowseForItemsXML��$��23��$��416,142,483,0q�$	��Top=�.��Browse�� -   $��PlayerEditor��$��Player��.��� �� -   $��
SaveEditor��$��Save Editor���� -   $��EnemyEditor��$��Enemies��.���    EnemyTemplate �� XPath  SelectedEnemyTemplate �� 
TargetType  EnemyListContainerStyle �� Property	 �� Value
 �� Triggers P� Property P� Value��%�   &	       &	 -     &	 Z     7  7  �� .R��� 
���   ����� $ @name���� .R��� 
���  ������ $ @name���� " ��.���  � ��8	   
 P�  �@��
IsSelected . . ���  � ��8	  .+��� -   $��image1��$��Right=�$��0,6,6,0q�$
��Fill=�$	��200��$	��200��$	��Top=��� -   $��AddNewEnemyButton��$��23��$��	4,437,0,0q�$	��Top=�$
��Left=�$��74.875��.��	Add New�� -   $��EnemyListBox��#��[ $��2.5,33,0,199.04q�$��200.5��$
��Left=�����  �� Source# [   � ContextMenu �� -   $��EnemyListConextBox�� J� 	AllowDrop . .@�m� -   $��NewTemplatedEnemy��$��Use As Template For New�� � ToolTip$O IOpens a window to add a new enemy using this enemy to fill out parameters��m� -   $��DeleteCurrentEnemy��$��Delete��$+ %Remove this enemy from the enemy list��m� -   $��AddNewEnemy��$��Add New��$* $Opens a window to create a new enemy���� -   $��label2��$��28��$��	2.5,4,0,0q�$	��Top=�
����iA�
�������$
��Bold"�$��200.5��$
��Left=�.��
Enemy List�� -   $��label7��$��28��$��	122,4,0,0q�$	��Top=�$
��Left=�$��46��$��Count��
�������$
��Bold"��� -   $��EnemyCountLabel��$��28��$
��Left=�$��146.11,4,0,0q�$	��Top=�$��53.75��$��Right=�$
��Bold"�
�����������  �� ElementName$ EnemeyListBox�� �� Path$ Items.Count��� -   $��EnemyLevelBox��$��	groupBox1��$	��164��$
��Left=�$��-4.5,0,0,2.04q�$��Bottom=�$��207.5�� � DataContext �� $ EnemyListBox��$ SelectedItem�.���� -   $��EnemyLevelsListBox��$	��125��$��112.274��$
��Left=�$��Bottom=����� $ EnemyInstance������ .R��� ���� $ @level���� -   $��label3��
����� �$��Available Levels��$
��Bold"�
�������$��28��$
��Left=�$��2.5,0,0,138.04q�$��Bottom=�$��200.5���� -   $��AddNewEnemyInstanceButton��$��23��$
��Left=�$��128,0,0,109.198q�$��Bottom=�$��75��.��	Add New� -   $��EnemyPropertiesGrid��$��218.867,8,6,8.04q� �� $ EnemyLevelsListBox��$ SelectedItem�.+��� -   $��label8��$��Enemy Description��$��28��$
��Left=�$��	13,87,0,0q�$	��Top=��� -   $��StatDescriptionBox��$��195.635��$��Right=�$��	0,6,6,412q�$	��200�� �� 
IsReadOnly . �� -   $��EnemyNameLabel��$��45.728��$
��Left=�$��7.336,6.183,0,0q�$	��Top=�$��308.664��$��20(��� -    $��EnemyDescriptionTextBox��$	��158��$
��Left=�$��	6,108,0,0q�$	��Top=�$	��310�� �� TextWrapping$ WrapWithOverflow=����� $ Description/@value���� -!   $��EnemyPropertyTabs��$��0,272,0,-8.04q�.@��� -"   $��EnemyStatsTab��$��Stats��.��� -#   $��EnemyStatsTabGrid��$	��322��$
��Left=�$	��736��.+��� -$   $��EnemyStatViewDisplay��$��0,6,325,0.96q� �� $ Stats������ $ 
Attributes� �� View �� .P���  �� Width$	 120��$��	Stat Name�� �� CellTemplate �� .R�� .+��� $	��120������ *Name+�� $	 250��$��
Stat Value�� �� .R�� .+��� $	��250������ *Value+�� -%   $��EnemyStatDescriptionBox��$��Right=�$��0,48,33,141q�$	��271��$
 Wrap=��� -&   $��label4��$��28��$��Right=�$��
0,21,184,0q�$	��Top=�$	��120��.��Stat Description�� -'   $��StatRatingRectangle��$��24��$��Right=�$��	0,0,33,71q�
���   �$��Bottom=�$	��271���� -(   $��EnemyStatusResistancesTab��$��Status Resistances��.��� -)   $��EnemyStatusResistanceGrid��.+��� -*   $ ��EnemyStatusResistancesGrid��$��4,4,0,6q�$
��Left=�$	��337��$ �� IsSynchronizedWithCurrentItem$
 TrueY�  Wpf.Util.GridViewSort   AutoSort . ���� $" StatusResistances/Resistance�� �� .P��� $	 220��$��Status Effect Name��   PropertyName$
 Name�� �� .R�� .+��� ���� $ @name���� $	 100��$��
Resistance�� �� .R�� .+��� $	��100������ $ @value���� -+   $#��EnemyElementalEffectivnessTab��$��Elemental Eff.��.��� -,   $(��"EnemyElementalEffectivenessTabGrid��.+��� --   $%��EnemyElementalEffectivenessGrid��$��4,4,0,36q�$
��Left=�$	��335������ $( "ElementEffectiveness/Effectiveness�� �� .P��� $	 220��$��Element Name�� �� DisplayMemberBinding �� $ @name�� �� .R�� .+��� ���� $ @name���� $	 100��$��Effectiveness�� �� .R�� .+��� $��70������ $ @value���� -.   $��EnemyDropTableTab��$��
Drop Table��.��� -/   $��EnemyDropTableGrid��.+��� -0   $��EnemyDropTable��$��
4,4,247,36q����� $ DropTable/Item�� �� .P��� $	 236��$��	Item Name�� �� .R�� .+��� $	��236������ $ @name���� $ 80��$
��Rate�� �� .R�� .+��� $��80������ $ @rate���� $ 80��$��Count�� �� .R�� .+��� $��80������ $ @count���� $ 80��$��	Variation�� �� .R�� .+��� $��80������ $ 
@variation���� -1   $��EnemyLootTableTab��$��
Loot Table��.��� -2   $��EnemyLootTableTabGrid��.+��� -3   $��EnemyLootTableGrid��$��
4,4,247,36q����� $ LootTable/Item�� �� .P��� $	 236��$��	Item Name�� �� .R�� .+��� $	��236������ $ @name���� $ 80��$
��Rate�� �� .R�� .+��� $��80������ $ @rate���� $ 80��$��Count�� �� .R�� .+��� $��80������ $ @count���� -4   $��EnemyAbilityTab��$��	Abilities��.��� �� -5   $��EnemyMagicTab��$��Usable Magic��.��� �� -6   $��EnemySkillsTab��$��Usable Skills��.��� �� -7   $��EnemyEquipmentTab��$��	Equipment���� -8   $��
EnemyAITab��$��AI��.��� .+��� -9   $��UsePreDefScriptsCheckBox��$��16��$
��Left=�$��6,28.58,0,0q�$	��Top=�$��142.9��.��Use pre-defined script�� -:   $��PreDefinedScripts��$
��Left=�$��6,50.015,0,0q�$��142.861��$��23.338��$	��Top=��� -;   $��EnemyScriptSource��$��236.414��$!��292.945,11.015,0.428,51.444q�$��424.576�� . {�.  �� -<   $��EnableCustomScript��$��16��$��282.942,0,141.471,30.009q�$��Bottom=�.��1/Use Custom Script (WARNING: For advanced users)�� -=   $��SaveToPreDefSource��$��23��$��Right=�$��0,0,7.861,25.722q�$��Bottom=�$��132.157��.��Save to Predefined List�� ->   $��EnemyMiscTab��$
��Misc��.��� .+��� -?   $��EnemySizeSelector��$��23��$
��Left=�$��92.885,6,0,0q�$	��Top=�$	��120��.@��� .��
Very Large�� .��Large�� .��Medium�� .��Small�� .��
Very Small�� -@   $��label5��$
��Left=�$��6,6,0,0q�$��81.453��$��29.054��$	��Top=�.��
Enemy Size�� -A   $��ActiveEnemyClasses��$
��Left=�$��8,75,0,104.198q�$	��100������ $ Classes/@value�� �� $ EnemyListBox��$ SelectedItem��� -B   $��AllEnemyClasses��$��147,75,0,104.198q�$
��Left=�$	��101������ $ Class/@value�� �� # [  $ ../AllClasses���� -C   $��	groupBox1��$��Enemy Flags��$��0,52.04,6,6q�$��Right=�$	��344��.��� .+��� -D   $��ImmuneToScanCheckBox��$��16��$��6,6,61.133,0q�$	��Top=�.��Immune To Scan�� -E   $��label1��$��28��$
��Left=�$��
147,41,0,0q�$	��Top=�$	��120��.��Available Classes�� -F   $��label6��$��28��$
��Left=�$��8,41,0,0q�$	��Top=�$	��120��.��Enemy Classes�� -G   $��SaveAllEnemiesButton��$��Save All...��$��23��$
��Left=�$��128,0,0,169.949q�$��Bottom=�$��75���� -H   $��EnemyPartyEditor��$��Enemy Parties��.��� �� -I   $��AbilityEditor��$��	Abilities��.��� �� -J   $��StatusEffectsEditor��$��Status Effects��.��� �� -K   $��AttackEditor��$��Attacks���� -L   $��
ItemEditor��$��Items��.���  �� $ ItemListBox��$ SelectedItem�   ItemTemplate  SelectedItemTemplate  ItemListContainerStyle��%�   &	       &	 -     &	 Z     7  7  �� .R��� 
���   ����� $ @name���� .R��� 
���  ������ $ @name���� " ��.���  � ��8	   
 P�  �@��
IsSelected . . ���  � ��8	  .+��� -M   $��ItemListBox��#��[ $
��Left=�$��	6,218,0,6q�$��227.5��$	��Top=�$	��405������ # [ �� -N   $��ActiveItemNameLabel��$��38.75��$
��Left=�$��6,6,0,0q�$	��Top=�$��225.25��$��20(�.��-�� -O   $��label11��
���i��$
��Bold"�
�������$��28��$
��Left=�$��	6,184,0,0q�$	��Top=�$��227.5��.��	Item List�� -P   $��label12��$
��Bold"�
�������$��28��$
��Left=�$��138,184,0,0q�$	��Top=�$��46��.��Count�� -Q   $��ItemCountLabel��$
��Bold"�
�������$��28��$��Right=�$��Right=�$��0,184,737,0q�$	��Top=�$��53.75������ $ EnemeyListBox��$ Items.Count��� -R   $��ItemDescriptionBox��$	��100��$
��Left=�$��6,78,0,0q�$	��Top=�$	��228��$��WrapWithOverflow=����� $ Description/@value�� �� �� -S   $��ItemIcon��$	��128��$	��128��$��Right=�$��	0,19,16,0q�$
��Fill=�$	��Top=��� -T   $��label13��$
��Icon��$��28��$��Right=�$��0,0,111.443,0q�$	��Top=�$��32.557���� -U   $��CommonPropertiesGorupBox��$��Common Properties��$	��254��$��240,19,183,0q�$	��Top=�.��� -V   $"��CommonPropertiesGorupBoxBrid��$	��535��$	��231�� � RowDefinitions �� $	��21* ��� $
��141* �.+��� -W   $��label15��$��Value��$��28��$
��Left=�$��1,6,0,0q�$	��Top=�$��2��$��39.533���� -X   $��ItemValueBox��$
��Left=�$��55,5,0,2q�$	��106������ $ @value���� -Y   $��listBox1��$��1��$
��Left=�$��6,61,0,5q�$	��120������ $ Classes/Class/@value���� -Z   $��listBox2��$��1��$��183,61,232,4q����� $  ../AllClasses/Class/@value���� -[   $��label16��$��Current Classes��$��1��$��28��$
��Left=�$��6,27,0,0q�$	��Top=�$��90.987���� -\   $��label17��$��Available Classes��$��28��$��183,27,252.963,0q�$	��Top=�$��1���� -]   $��ComponentList��$��1��$	��150��$
��Left=�$��	339,0,0,0q�$	��Top=�$	��152������ $ Components/*������ .R��� ���� *Name+�� -^   $��label18��$��Available Components��$��2��$��28��$
��Left=�$��	339,4,0,0q�$	��Top=��� -_   $��AddComponent��$��Add Comp��$��1��$��23��$
��Left=�$��340,156,0,0q�$	��Top=�$��75���� -`   $��label14��$��28��$
��Left=�$��3,1,0,0q�$	��Top=�$��47��$��1��.��Family�� -a   $��
ItemFamily��$��23��$��55,4,0,0q�$	��Top=�$
��Left=�$	��106��$��1������ $ Family/@value���� -b   $��OtherFamilyMembers��$��1��$��23��$��183,4,232,0q�$	��Top=��� -c   $��ActiveComponentGrouping��$��Active Component��$	��334��$
��Left=�$��272,289,0,0q�$	��Top=�$	��683��.��� �� -d   $��	MapEditor��$
��Maps��.��� �� -e   $��AnimationEditor��$��	Animation���� -f   $��AudioEditor��$��Audio��.��� �� -g   $��GameConfiguration��$��Game Config��