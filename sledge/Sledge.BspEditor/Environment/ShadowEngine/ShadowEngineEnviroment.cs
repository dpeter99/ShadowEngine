using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LogicAndTrick.Oy;
using Sledge.BspEditor.Compile;
using Sledge.BspEditor.Documents;
using Sledge.BspEditor.Environment.Empty;
using Sledge.BspEditor.Primitives.MapData;
using Sledge.BspEditor.Providers;
using Sledge.BspEditor.Providers.ShadowEngine;
using Sledge.Common.Shell.Commands;
using Sledge.DataStructures.GameData;
using Sledge.DataStructures.Geometric;
using Sledge.FileSystem;
using Sledge.Providers.Texture;

namespace Sledge.BspEditor.Environment.ShadowEngine
{
    public class ShadowEngineEnviroment : IEnvironment
    {
        public string Engine => "ShadowEngine";
        public string ID { get; set; }
        public string Name { get; set; }
        public IFile Root => null;
        public IEnumerable<string> Directories => new string[0];

        public string BaseDirectory { get; set; }

        public ShadowEngineEnviroment()
        {
            
        }

        public async Task<TextureCollection> GetTextureCollection()
        {
            return new EmptyTextureCollection(new TexturePackage[0]);
        }

        public async Task<GameData> GetGameData()
        {
            return new GameData();
        }

        public Task UpdateDocumentData(MapDocument document)
        {
            return Task.FromResult(0);
        }

        public void AddData(IEnvironmentData data)
        {

        }

        public IEnumerable<T> GetData<T>() where T : IEnvironmentData
        {
            return null;
        }

        private async Task ExportDocumentForBatch(MapDocument doc, string path, Box cordonBounds)
        {
            var cordonTextureName = "BLACK"; // todo make this configurable

            if (cordonBounds != null && !cordonBounds.IsEmpty())
            {
                doc = doc.CloneWithCordon(cordonBounds, cordonTextureName);
            }

            await Oy.Publish("Command:Run", new CommandMessage("Internal:ExportDocument", new
            {
                Document = doc,
                Path = path,
                LoaderHint = nameof(ShmfSourceProvider)
            }));
        }

        public Task<Batch> CreateBatch(IEnumerable<BatchArgument> arguments, BatchOptions options)
        {

            var batch = new Batch();

            // Create the working directory
            batch.Steps.Add(new BatchCallback(BatchStepType.CreateWorkingDirectory, async (b, d) =>
            {
                var workingDir = options.WorkingDirectory ?? Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                if (!Directory.Exists(workingDir)) Directory.CreateDirectory(workingDir);
                b.Variables["WorkingDirectory"] = workingDir;

                await Oy.Publish("Compile:Debug", $"Working directory is: {workingDir}\r\n");
            }));

            // Save the file to the working directory
            batch.Steps.Add(new BatchCallback(BatchStepType.ExportDocument, async (b, d) =>
            {
                var fn = options.MapFileName ?? d.FileName;
                var ext = options.MapFileExtension ?? ".map";

                if (String.IsNullOrWhiteSpace(fn) || fn.IndexOf('.') < 0) fn = Path.GetRandomFileName();
                var mapFile = Path.GetFileNameWithoutExtension(fn) + ext;
                b.Variables["MapFileName"] = mapFile;

                var path = Path.Combine(b.Variables["WorkingDirectory"], mapFile);
                b.Variables["MapFile"] = path;

                if (options.ExportDocument != null)
                {
                    await options.ExportDocument(d, path);
                }
                else
                {
                    var useCordon = options.UseCordonBounds.GetValueOrDefault(true);
                    Box bounds = null;
                    if (useCordon && options.CordonBounds != null)
                    {
                        bounds = options.CordonBounds;
                    }
                    else if (useCordon)
                    {
                        var cb = d.Map.Data.GetOne<CordonBounds>();
                        if (cb != null && cb.Enabled && !cb.Box.IsEmpty()) bounds = cb.Box;
                    }
                    await ExportDocumentForBatch(d, path, bounds);
                }

                await Oy.Publish("Compile:Debug", $"Map file is: {path}\r\n");
            }));

            return Task.FromResult<Batch>(null);
        }

        public IEnumerable<AutomaticVisgroup> GetAutomaticVisgroups()
        {
            yield break;
        }

        public bool IsNullTexture(string name)
        {
            return false;
        }

        public string DefaultBrushEntity => "";
        public string DefaultPointEntity => "";
        public decimal DefaultTextureScale => 1;

        
    }
}
