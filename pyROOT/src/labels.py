import numpy as np


interaction_codes = {
    0: "QE",
    1: "RES",
    2: "DIS",
    3: "Coherent",
    4: "Coherent Elastic",
    5: "Electron scatt.",
    6: "IMDAnnihilation",
    7: r"Inverse $\beta$ decay",
    8: "Glashow resonance",
    9: "AMNuGamma",
    10: "MEC",
    11: "Diffractive",
    12: "EM",
    13: "Weak Mix"
}

interaction_code_colors = {
    0: 2,
    1: 4,
    2: 6,
    3: 3,
    4: 5,
    5: 7,
    6: 8,
    7: 9,
    8: 10,
    9: 11,
    10: 12,
    11: 13,
    12: 14,
    13: 15,
}


pdg_labels = {
        14:"#nu_{#mu}",
        -14:"#hbar{#nu}_{#mu}",
        12:"#nu_{e}",
        -12:"#hbar{#nu}_{e}",
        13:"#mu^{-}",
        -13:"#mu^{+}",
        221:"#eta",
        22:"#gamma",

}


labels = {
        0:"#eta" + " "+ "#rightarrow" + " other: ",
        1:"out of FV: ", # nu interactions outside fidu
        2:"#nu other: ",
        3:"1 #pi^{0}: ",
        4:"2+#pi^{0}: ",
        5:"#nu_{#mu}#eta"+ " "+"#rightarrow"+" "+"#gamma#gamma: ",
        6:"cosmic: "
}

labels0 = {
        0: "Cosmic ",
        1: "#nu out of FV ",
        2: "#eta other ",
        3: "#nu other ",
        4: "#nu#eta"+ " "+ "#rightarrow"+ " " + "#gamma#gamma ",
        5: "#nu#eta"+ " "+ "#rightarrow"+ " " + "1 #pi^{0} ",
        6: "#nu#eta"+ " "+ "#rightarrow"+ " " + "2+ #pi^{0} "
}
